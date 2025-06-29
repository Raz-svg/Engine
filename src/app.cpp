#include "core/app.hpp"


APP::APP()
{
    isrunning = true;
    need_rerender = false;
    is_resizing = false;
    pending_resize = false;
    pwindow = nullptr;
    prenderer = nullptr;
    
    // Performance settings
    use_low_res_preview = true;
    use_multithreading = true;
    progressive_rendering = true;
    real_time_resize = true;
    preview_scale_factor = 0.25; // Start with 1/4 resolution for preview
    last_resize_time = 0;
    current_window_width = 0;
    current_window_height = 0;
    
    // Multi-threading setup
    num_threads = std::max(1, static_cast<int>(std::thread::hardware_concurrency()));
    tile_size = 64; // 64x64 pixel tiles for good load balancing
    render_in_progress = false;
    completed_tiles = 0;
    
    // Progressive rendering setup
    progressive_scales = {8, 4, 2, 1}; // 1/8, 1/4, 1/2, full resolution
    current_progressive_level = 0;
    is_progressive_complete = false;
    
    printf("Initialized with %d threads, tile size %dx%d\n", num_threads, tile_size, tile_size);
}

bool APP::oninit(){
    
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        return false;
    }

    pwindow=SDL_CreateWindow("Raytracer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        camera.image_width,camera.image_height,
        SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN);
    if(pwindow != nullptr){
        prenderer =SDL_CreateRenderer(pwindow,-1,0);
        
        printf("Camera dimensions: %fx%f\n", camera.image_width, camera.image_height);
        image.initialize(camera.image_width, camera.image_height, prenderer);
        
        // Initialize preview image at lower resolution
        double preview_width = camera.image_width * preview_scale_factor;
        double preview_height = camera.image_height * preview_scale_factor;
        preview_image.initialize(preview_width, preview_height, prenderer);
        
        // Initialize current window size
        SDL_GetWindowSize(pwindow, &current_window_width, &current_window_height);
    }
    
    return (pwindow != nullptr && prenderer != nullptr);
}

int APP::onexecute(){

    SDL_Event event;
    if(oninit()==false){
        return -1;
    }
    while(isrunning){
        while(SDL_PollEvent(&event)!=0){
            onevent(&event);
        }
        onloop();
        onrender();
    }
    onexit();
    return 0;


}


void APP::onevent(SDL_Event *event){

    if(event->type ==SDL_QUIT){
        isrunning=false;
    }
    if (event->type == SDL_WINDOWEVENT) {
        if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
            // This fires continuously during resize - perfect for real-time updates!
            int new_width = event->window.data1;
            int new_height = event->window.data2;
            
            // Update current window size immediately
            current_window_width = new_width;
            current_window_height = new_height;
            last_resize_time = SDL_GetTicks();
            
            // Only update camera aspect ratio
            if (new_width > 100 && new_height > 100 && new_width < 5000 && new_height < 5000) {
                camera.set_aspect_ratio(static_cast<double>(new_width) / static_cast<double>(new_height));
                
                if (real_time_resize) {
                    // Render a quick low-res preview immediately
                    render_quick_preview(new_width, new_height);
                } else {
                    // Use the old debounced approach
                    pending_resize = true;
                }
            }
        }
    }
}

void APP::onloop(){
    static bool initial_rendered = false;
    
    // Check if we need to handle a pending resize (debounced system)
    if (pending_resize && !real_time_resize) {
        uint32_t current_time = SDL_GetTicks();
        
        // If enough time has passed since the last resize event, process it
        if (current_time - last_resize_time >= RESIZE_DEBOUNCE_MS) {
            printf("Processing resize to %dx%d...\n", current_window_width, current_window_height);
            
            // Update camera and image dimensions to match window
            camera.update_dimensions(static_cast<double>(current_window_width), 
                                   static_cast<double>(current_window_height));
            image.resize(static_cast<double>(current_window_width), 
                        static_cast<double>(current_window_height));
            
            // Reset progressive rendering
            current_progressive_level = 0;
            is_progressive_complete = false;
            
            need_rerender = true;
            pending_resize = false;
        }
    }
    
    // For real-time resize, check if we should do a full render after resize stops
    if (real_time_resize) {
        uint32_t current_time = SDL_GetTicks();
        if (current_time - last_resize_time >= RESIZE_DEBOUNCE_MS && 
            (current_window_width != static_cast<int>(camera.image_width) || 
             current_window_height != static_cast<int>(camera.image_height))) {
            
            printf("Starting full resolution render after resize\n");
            camera.update_dimensions(static_cast<double>(current_window_width), 
                                   static_cast<double>(current_window_height));
            image.resize(static_cast<double>(current_window_width), 
                        static_cast<double>(current_window_height));
            
            current_progressive_level = 0;
            is_progressive_complete = false;
            need_rerender = true;
        }
    }
    
    // Only render if we haven't rendered yet, or if we need to re-render
    if (!initial_rendered || need_rerender) {
        if (progressive_rendering && !is_progressive_complete) {
            render_progressive(progressive_scales[current_progressive_level]);
            current_progressive_level++;
            if (current_progressive_level >= static_cast<int>(progressive_scales.size())) {
                is_progressive_complete = true;
                printf("Progressive rendering complete.\n");
            }
        } else if (use_multithreading) {
            render_multithreaded();
        } else {
            // Fallback to single-threaded rendering
            if (need_rerender) {
                printf("Re-rendering at %dx%d resolution...\n", 
                       static_cast<int>(camera.image_width), static_cast<int>(camera.image_height));
            }
            
            for (int j = 0; j < camera.image_height; ++j) {
                for (int i = 0; i < camera.image_width; ++i) {
                    Ray r = camera.get_ray(i, j);
                    color pixel_color = ray_color(r);
                    image.setpixel(i, j, pixel_color.x(), pixel_color.y(), pixel_color.z());
                }
            }
            
            if (need_rerender) {
                printf("Re-render complete.\n");
            }
        }
        
        initial_rendered = true;
        need_rerender = false;
    }
}

void APP::onrender(){
    SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255);
    SDL_RenderClear(prenderer);

    // If we have a pending resize, scale the existing image to fit the new window size
    if (pending_resize && current_window_width > 0 && current_window_height > 0) {
        image.display_scaled(current_window_width, current_window_height);
    } else {
        // Normal display - let SDL scale automatically
        image.display();
    }

    SDL_RenderPresent(prenderer);
}

void APP::onexit(){
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    pwindow =nullptr;
    SDL_Quit();
}

// Basic ray color function - creates a simple gradient background
color APP::ray_color(const Ray& r) const {
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

// Render a specific tile of the image
void APP::render_tile(const RenderTile& tile, Image* target_image, Camera* target_camera) {
    for (int j = tile.start_y; j < tile.end_y; ++j) {
        for (int i = tile.start_x; i < tile.end_x; ++i) {
            if (i < target_camera->image_width && j < target_camera->image_height) {
                Ray r = target_camera->get_ray(i, j);
                color pixel_color = ray_color(r);
                target_image->setpixel(i, j, pixel_color.x(), pixel_color.y(), pixel_color.z());
            }
        }
    }
}

// Progressive rendering - start with low resolution, then refine
void APP::render_progressive(int resolution_scale) {
    int width = static_cast<int>(camera.image_width);
    int height = static_cast<int>(camera.image_height);
    
    printf("Progressive render level: 1/%d resolution\n", resolution_scale);
    
    // For scales > 1, render at reduced resolution and upscale
    if (resolution_scale > 1) {
        for (int j = 0; j < height; j += resolution_scale) {
            for (int i = 0; i < width; i += resolution_scale) {
                Ray r = camera.get_ray(i, j);
                color pixel_color = ray_color(r);
                
                // Fill a block of pixels with the same color
                for (int dy = 0; dy < resolution_scale && j + dy < height; ++dy) {
                    for (int dx = 0; dx < resolution_scale && i + dx < width; ++dx) {
                        image.setpixel(i + dx, j + dy, pixel_color.x(), pixel_color.y(), pixel_color.z());
                    }
                }
            }
        }
    } else {
        // Full resolution - use multithreading if available
        render_multithreaded();
    }
}

// Multi-threaded tile-based rendering
void APP::render_multithreaded() {
    if (render_in_progress.load()) {
        return; // Already rendering
    }
    
    render_in_progress = true;
    completed_tiles = 0;
    
    int width = static_cast<int>(camera.image_width);
    int height = static_cast<int>(camera.image_height);
    
    // Create tiles
    std::vector<RenderTile> tiles;
    int tile_id = 0;
    
    for (int y = 0; y < height; y += tile_size) {
        for (int x = 0; x < width; x += tile_size) {
            RenderTile tile;
            tile.start_x = x;
            tile.end_x = std::min(x + tile_size, width);
            tile.start_y = y;
            tile.end_y = std::min(y + tile_size, height);
            tile.tile_id = tile_id++;
            tiles.push_back(tile);
        }
    }
    
    printf("Rendering %zu tiles using %d threads...\n", tiles.size(), num_threads);
    
    // Launch worker threads
    std::vector<std::future<void>> futures;
    std::atomic<size_t> tile_index(0);
    
    for (int t = 0; t < num_threads; ++t) {
        futures.push_back(std::async(std::launch::async, [&]() {
            size_t local_tile_index;
            while ((local_tile_index = tile_index.fetch_add(1)) < tiles.size()) {
                render_tile(tiles[local_tile_index], &image, &camera);
                completed_tiles++;
                
                // Progress reporting every 10 tiles
                if (completed_tiles % 10 == 0) {
                    printf("Completed %d/%zu tiles\n", completed_tiles.load(), tiles.size());
                }
            }
        }));
    }
    
    // Wait for all threads to complete
    for (auto& future : futures) {
        future.wait();
    }
    
    printf("Multi-threaded rendering complete. Rendered %zu tiles.\n", tiles.size());
    render_in_progress = false;
}

// Render a quick low-resolution preview during resize
void APP::render_quick_preview(int width, int height) {
    // Create a temporary camera with the new dimensions
    Camera temp_camera = camera;
    temp_camera.update_dimensions(static_cast<double>(width), static_cast<double>(height));
    
    // Calculate low-resolution dimensions
    int preview_width = static_cast<int>(width * preview_scale_factor);
    int preview_height = static_cast<int>(height * preview_scale_factor);
    
    // Skip if too small
    if (preview_width < 10 || preview_height < 10) return;
    
    // Resize the preview image
    preview_image.resize(static_cast<double>(preview_width), static_cast<double>(preview_height));
    
    // Render at low resolution - this should be very fast
    for (int j = 0; j < preview_height; ++j) {
        for (int i = 0; i < preview_width; ++i) {
            Ray r = temp_camera.get_ray(i, j);
            color pixel_color = ray_color(r);
            preview_image.setpixel(i, j, pixel_color.x(), pixel_color.y(), pixel_color.z());
        }
    }
    
    printf("Quick preview rendered: %dx%d\n", preview_width, preview_height);
}
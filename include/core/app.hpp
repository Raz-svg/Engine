#ifndef APP_H
#define APP_H

#include<SDL2/SDL.h>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <future>
#include <chrono>
#include "rendering/camera.hpp"
#include "rendering/image.hpp"

struct RenderTile {
    int start_x, end_x;
    int start_y, end_y;
    int tile_id;
};

class APP{
    public:

        APP();

        int onexecute();
        bool oninit();
        void onevent(SDL_Event *event);
        void onloop();
        void onrender();
        void onexit();
        
        // Raytracing functions
        color ray_color(const Ray& r) const;
        void render_tile(const RenderTile& tile, Image* target_image, Camera* target_camera);
        void render_progressive(int resolution_scale = 1);
        void render_multithreaded();
        void render_quick_preview(int width, int height);

    private:
        
        Camera camera;
        Image image;
        Image preview_image; // Lower resolution image for fast preview
        bool isrunning;
        bool need_rerender;
        bool is_resizing;
        SDL_Window *pwindow;
        SDL_Renderer *prenderer;
        
        // Performance optimization variables
        bool use_low_res_preview;
        bool use_multithreading;
        bool progressive_rendering;
        bool real_time_resize;
        double preview_scale_factor;
        uint32_t last_resize_time;
        int current_window_width;
        int current_window_height;
        bool pending_resize;
        static const uint32_t RESIZE_DEBOUNCE_MS = 300;
        
        // Multi-threading variables
        int num_threads;
        int tile_size;
        std::atomic<bool> render_in_progress;
        std::atomic<int> completed_tiles;
        std::mutex render_mutex;
        
        // Progressive rendering
        std::vector<int> progressive_scales; // e.g., [8, 4, 2, 1] for 1/8, 1/4, 1/2, full res
        int current_progressive_level;
        bool is_progressive_complete;

};

#endif
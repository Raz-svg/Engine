#include "rendering/image.hpp"
#include <fstream>
#include <cstring>
#include <cmath>

Image::Image(){
    m_xSize = 0.0;
    m_ySize = 0.0;
    m_intXSize = 0;
    m_intYSize = 0;
    m_pTexture = nullptr;
    m_pRenderer = nullptr;
}

Image::~Image(){
    if(m_pTexture != nullptr)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}

void Image::initialize(const double xSize, const double ySize, SDL_Renderer *prenderer) {
    m_xSize = xSize;
    m_ySize = ySize;
    m_pRenderer = prenderer;
    
    // Cache integer versions for performance
    m_intXSize = static_cast<int>(xSize);
    m_intYSize = static_cast<int>(ySize);
  
    // Allocate contiguous pixel array for better cache performance
    m_pixels.resize(m_intXSize * m_intYSize);
    
    InitTexture();
}

// Fast pixel setting for performance-critical paths
void Image::setpixel(const double x, const double y, const double red, const double green, const double blue) {
    int int_x = static_cast<int>(x);
    int int_y = static_cast<int>(y);
    
    // Bounds check
    if (int_x >= 0 && int_x < m_intXSize && int_y >= 0 && int_y < m_intYSize) {
        int index = int_y * m_intXSize + int_x; // Row-major order for cache efficiency
        m_pixels[index] = Pixel(red, green, blue);
    }
}

// Thread-safe version for multi-threaded rendering
void Image::setpixel_safe(const double x, const double y, const double red, const double green, const double blue) {
    int int_x = static_cast<int>(x);
    int int_y = static_cast<int>(y);
    
    if (int_x >= 0 && int_x < m_intXSize && int_y >= 0 && int_y < m_intYSize) {
        int index = int_y * m_intXSize + int_x;
        std::lock_guard<std::mutex> lock(m_textureMutex);
        m_pixels[index] = Pixel(red, green, blue);
    }
}

// Set a block of pixels to the same color (useful for progressive rendering)
void Image::setpixel_block(int start_x, int start_y, int end_x, int end_y, const double red, const double green, const double blue) {
    Pixel pixel(red, green, blue);
    
    for (int y = start_y; y < end_y && y < m_intYSize; ++y) {
        for (int x = start_x; x < end_x && x < m_intXSize; ++x) {
            int index = y * m_intXSize + x;
            m_pixels[index] = pixel;
        }
    }
}

void Image::display() {
    create_texture_from_pixels();
    
    // Render the texture
    SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, nullptr);
}

void Image::create_texture_from_pixels() {
    // Safety checks
    if (m_intXSize <= 0 || m_intYSize <= 0) {
        printf("Error: Invalid image dimensions %dx%d\n", m_intXSize, m_intYSize);
        return;
    }
    
    if (m_pRenderer == nullptr) {
        printf("Error: Renderer is null\n");
        return;
    }
    
    if (m_pixels.empty()) {
        printf("Error: No pixel data\n");
        return;
    }
    
    SDL_Surface* surface = SDL_CreateRGBSurface(0, m_intXSize, m_intYSize, 32, 
        0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    
    if (surface == nullptr) {
        printf("Error creating surface: %s\n", SDL_GetError());
        return;
    }
    
    // Lock surface for pixel access
    SDL_LockSurface(surface);
    Uint32* pixels = (Uint32*)surface->pixels;
    
    // Write our raytraced pixels to the surface - optimized loop
    for (int y = 0; y < m_intYSize; ++y) {
        for (int x = 0; x < m_intXSize; ++x) {
            int src_index = y * m_intXSize + x;
            int dst_index = y * m_intXSize + x;
            
            const Pixel& pixel = m_pixels[src_index];
            pixels[dst_index] = ConvertColor(pixel.r, pixel.g, pixel.b);
        }
    }
    
    SDL_UnlockSurface(surface);
    
    // Thread-safe texture creation
    {
        std::lock_guard<std::mutex> lock(m_textureMutex);
        if (m_pTexture) SDL_DestroyTexture(m_pTexture);
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
    }
    
    SDL_FreeSurface(surface);
}

void Image::display_scaled(int window_width, int window_height) {
    create_texture_from_pixels();
    
    // Calculate scaling to maintain aspect ratio
    double image_aspect = static_cast<double>(m_intXSize) / static_cast<double>(m_intYSize);
    double window_aspect = static_cast<double>(window_width) / static_cast<double>(window_height);
    
    SDL_Rect dest_rect;
    
    if (image_aspect > window_aspect) {
        // Image is wider relative to window - fit to width
        dest_rect.w = window_width;
        dest_rect.h = static_cast<int>(window_width / image_aspect);
        dest_rect.x = 0;
        dest_rect.y = (window_height - dest_rect.h) / 2;
    } else {
        // Image is taller relative to window - fit to height
        dest_rect.h = window_height;
        dest_rect.w = static_cast<int>(window_height * image_aspect);
        dest_rect.x = (window_width - dest_rect.w) / 2;
        dest_rect.y = 0;
    }
    
    // Render the texture scaled to fit the window
    SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, &dest_rect);
}

void Image::InitTexture() {
    
}

Uint32 Image::ConvertColor(const double red, const double green, const double blue) {
   
    Uint8 r = (Uint8)(255 * fmax(0.0, fmin(1.0, red)));
    Uint8 g = (Uint8)(255 * fmax(0.0, fmin(1.0, green)));
    Uint8 b = (Uint8)(255 * fmax(0.0, fmin(1.0, blue)));
    Uint8 a = 255;
    
    return (a << 24) | (b << 16) | (g << 8) | r;
}

void Image::resize(const double new_xSize, const double new_ySize) {
    // Safety checks
    if (new_xSize <= 0 || new_ySize <= 0 || new_xSize > 5000 || new_ySize > 5000) {
        printf("Resize rejected: invalid dimensions %.0fx%.0f\n", new_xSize, new_ySize);
        return;
    }
    
    m_xSize = new_xSize;
    m_ySize = new_ySize;
    
    // Cache integer versions
    m_intXSize = static_cast<int>(new_xSize);
    m_intYSize = static_cast<int>(new_ySize);
    
    // Resize pixel array
    m_pixels.clear();
    m_pixels.resize(m_intXSize * m_intYSize);
    
    // Don't recreate texture here - let display() handle it
}
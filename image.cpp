#include "image.hpp"
#include <fstream>
#include <cstring>
#include <cmath>

Image::Image(){
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = nullptr;
    m_pRenderer = nullptr;
}

Image::~Image(){
    if(m_pTexture != nullptr)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}

void Image::initialize(const int xSize, const int ySize, SDL_Renderer *prenderer) {
    // Store dimensions and renderer
    m_xSize = xSize;
    m_ySize = ySize;
    m_pRenderer = prenderer;
    
    // Resize pixel arrays
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    
    InitTexture();
}

void Image::setpixel(const int x, const int y, const double red, const double green, const double blue) {
    if (x >= 0 && x < m_xSize && y >= 0 && y < m_ySize) {
        m_rChannel[x][y] = red;
        m_gChannel[x][y] = green;
        m_bChannel[x][y] = blue;
    }
}

void Image::display() {
    // Create a surface with our pixel data
    SDL_Surface* surface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, 
        0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    
    if (surface == nullptr) return;
    
    // Lock the surface for direct pixel access
    SDL_LockSurface(surface);
    
    Uint32* pixels = (Uint32*)surface->pixels;
    
    // Write our raytraced pixels to the surface
    for (int y = 0; y < m_ySize; ++y) {
        for (int x = 0; x < m_xSize; ++x) {
            Uint32 color = ConvertColor(m_rChannel[x][y], m_gChannel[x][y], m_bChannel[x][y]);
            pixels[y * m_xSize + x] = color;
        }
    }
    
    SDL_UnlockSurface(surface);
    
    // Convert surface to texture
    if (m_pTexture) SDL_DestroyTexture(m_pTexture);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
    
    // Render the texture
    SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, nullptr);
    
    // Clean up surface
    SDL_FreeSurface(surface);
}

void Image::InitTexture() {
    // Nothing needed here for this approach
}

Uint32 Image::ConvertColor(const double red, const double green, const double blue) {
    // Clamp values to [0,1] and convert to 0-255
    Uint8 r = (Uint8)(255 * fmax(0.0, fmin(1.0, red)));
    Uint8 g = (Uint8)(255 * fmax(0.0, fmin(1.0, green)));
    Uint8 b = (Uint8)(255 * fmax(0.0, fmin(1.0, blue)));
    Uint8 a = 255;
    
    return (a << 24) | (b << 16) | (g << 8) | r;
}
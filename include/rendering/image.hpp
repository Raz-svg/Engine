#ifndef  IMAGE_H
#define IMAGE_H

#include<string>
#include<vector>
#include<SDL2/SDL.h>
#include<mutex>

// Structure for better cache locality - pack RGB together
struct alignas(32) Pixel {
    double r, g, b;
    Pixel() : r(0.0), g(0.0), b(0.0) {}
    Pixel(double red, double green, double blue) : r(red), g(green), b(blue) {}
};

class Image{

    public:
        Image();
       ~Image();

       void initialize(const double xSize, const double ySize, SDL_Renderer *prenderer);
       
       // Optimized pixel setting with bounds checking
       void setpixel(const double x, const double y, const double red, const double green, const double blue);
       void setpixel_safe(const double x, const double y, const double red, const double green, const double blue);
       
       // Bulk pixel operations for better performance
       void setpixel_block(int start_x, int start_y, int end_x, int end_y, const double red, const double green, const double blue);

       void display();
       void display_scaled(int window_width, int window_height);
	   void resize(const double new_xSize, const double new_ySize);
	   
	   double get_width() const { return m_xSize; }
	   double get_height() const { return m_ySize; }

    private:
        Uint32 ConvertColor(const double red, const double green, const double blue);
		void InitTexture();
		void create_texture_from_pixels();
    
    private:
		// More cache-friendly pixel storage - single contiguous array
		std::vector<Pixel> m_pixels;
		
		// Image dimensions
		double m_xSize, m_ySize;
		int m_intXSize, m_intYSize; // Cache integer versions
		
		// SDL2 stuff
		SDL_Renderer *m_pRenderer;
		SDL_Texture *m_pTexture;
		
		// Thread safety for multi-threaded rendering
		std::mutex m_textureMutex;
};

#endif
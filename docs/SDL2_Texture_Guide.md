# SDL2 Texture Rendering Guide

This guide demonstrates how to work with textures in SDL2, including creating textures from surfaces and rendering them.

## Key Concepts

### 1. SDL_Surface vs SDL_Texture

- **SDL_Surface**: Software-based image representation stored in system RAM
- **SDL_Texture**: Hardware-accelerated image representation stored in GPU memory
- Textures are faster for rendering but can't be directly manipulated pixel-by-pixel

### 2. Creating Textures from Surfaces

```cpp
// Method 1: Create surface from pixel data
SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
    pixels,     // pixel data
    width,      // width
    height,     // height
    32,         // depth (bits per pixel)
    width * 4,  // pitch (bytes per row)
    rmask, gmask, bmask, amask  // color masks
);

// Method 2: Load from file
SDL_Surface* surface = SDL_LoadBMP("image.bmp");

// Convert surface to texture
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

// Always free the surface after creating texture
SDL_FreeSurface(surface);
```

### 3. Rendering Textures

```cpp
// Basic rendering (uses texture's original size)
SDL_RenderCopy(renderer, texture, NULL, NULL);

// Render at specific position
SDL_Rect destRect = {x, y, width, height};
SDL_RenderCopy(renderer, texture, NULL, &destRect);

// Render portion of texture
SDL_Rect srcRect = {src_x, src_y, src_w, src_h};
SDL_Rect destRect = {dest_x, dest_y, dest_w, dest_h};
SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
```

### 4. Color Masks for Different Byte Orders

```cpp
Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
```

## Example Usage in Your Project

### Creating a Gradient Texture

```cpp
void CreateGradientTexture() {
    const int width = 256, height = 256;
    Uint32* pixels = new Uint32[width * height];
    
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Uint8 red = x;
            Uint8 green = y;
            Uint8 blue = 128;
            Uint8 alpha = 255;
            
            pixels[y * width + x] = (alpha << 24) | (blue << 16) | (green << 8) | red;
        }
    }
    
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        pixels, width, height, 32, width * 4,
        0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
    );
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Use texture...
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    delete[] pixels;
}
```

### Loading and Rendering an Image

```cpp
bool LoadAndRenderImage(const char* filename) {
    SDL_Surface* surface = SDL_LoadBMP(filename);
    if (!surface) {
        printf("Failed to load %s: %s\n", filename, SDL_GetError());
        return false;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        return false;
    }
    
    // Get texture dimensions
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    
    // Render texture
    SDL_Rect destRect = {100, 100, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    
    SDL_DestroyTexture(texture);
    return true;
}
```

## Best Practices

1. **Always destroy textures** when done: `SDL_DestroyTexture(texture)`
2. **Free surfaces** after creating textures: `SDL_FreeSurface(surface)`
3. **Check for NULL** returns from texture creation functions
4. **Use textures for rendering**, surfaces for pixel manipulation
5. **Batch texture operations** for better performance
6. **Consider texture streaming** for dynamic content

## Common Pitfalls

1. Forgetting to free surfaces and textures (memory leaks)
2. Using wrong color masks for the target platform
3. Modifying pixel data after creating surface without updating texture
4. Not checking for SDL errors when operations fail

## Supported Image Formats

- **SDL_LoadBMP()**: Only BMP files
- **For other formats**: Use SDL_image extension
  ```cpp
  #include <SDL2/SDL_image.h>
  
  SDL_Surface* surface = IMG_Load("image.png"); // PNG, JPG, etc.
  ```

This implementation in your project provides a solid foundation for working with SDL2 textures in your raytracer application.

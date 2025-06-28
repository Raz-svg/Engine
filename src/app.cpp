#include "core/app.hpp"


APP::APP()
{

    isrunning =true;
    pwindow=nullptr;
    prenderer=nullptr;
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
        
        // Initialize the image for raytracing output
        image.initialize(camera.image_width, camera.image_height, prenderer);
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
}

void APP::onloop(){
    // Simple raytracing example - create a gradient
    static bool rendered = false;
    if (!rendered) {
        // Render your raytraced scene here
        for (int y = 0; y < camera.image_height; ++y) {
            for (int x = 0; x < camera.image_width; ++x) {
                // Simple gradient as example (replace with your raytracing)
                double r = double(x) / camera.image_width;
                double g = double(y) / camera.image_height;
                double b = 0.2;
                
                image.setpixel(x, y, r, g, b);
            }
        }
        rendered = true;
    }
}

void APP::onrender(){
    SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255);
    SDL_RenderClear(prenderer);

    // Display the raytraced image
    image.display();

    SDL_RenderPresent(prenderer);
}

void APP::onexit(){

    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    pwindow =nullptr;
    SDL_Quit();
}
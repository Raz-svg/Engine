#ifndef APP_H
#define APP_H

#include<SDL2/SDL.h>
#include "camera.hpp"
#include "image.hpp"
class APP{
    public:

        APP();

        int onexecute();
        bool oninit();
        void onevent(SDL_Event *event);
        void onloop();
        void onrender();
        void onexit();

    private:
        
        Camera camera;
        Image image;
        bool isrunning;
        SDL_Window *pwindow;
        SDL_Renderer *prenderer;

};

#endif
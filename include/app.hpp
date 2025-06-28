#ifndef APP_H
#define APP_H

#include<SDL2/SDL.H>

class APP{
    public:

        APP();

        int onexecute();
        bool oninti();
        void onevent(SDL_EVENT *event);
        void onloop();
        void onrender();
        void onexit();

    private:
       
        Image image;
        bool isrunning;
        SDL_Window *pwindow;
        SDL_Renderer *prenderer;


}
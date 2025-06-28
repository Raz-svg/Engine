#include "app.h"

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
        1200,720,
        SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN);
    if(pwindow != nullptr){
        prenderer =SDL_CreateRenderer(pwinode,-1,0);





    }
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

}

void APP::onrender(){
    SDL_SetRenderDrawColor(prenderer,255,255,255,255);
    SDL_RenderClear(prenderer);

    SDL_RenderPresent(prenderer);
}

void APP::onexit(){

    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    pwindow =nullptr;
    SDL_Quit();
}
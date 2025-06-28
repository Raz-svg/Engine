#include "image.hpp"
#include<fstream>

Image::Image(){

    m_xSize =0;
    m_ySize=0;
    m_pTexture =nullptr;
}

Image::~Image(){
    if(m_pTexture!=nullptr)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}
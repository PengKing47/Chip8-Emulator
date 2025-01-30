#include "sdlscreen.h"

SDLScreen::SDLScreen(){
    this->window = nullptr;
    this->renderer = nullptr;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &this->window, &this->renderer);
    SDL_SetWindowResizable(this->window, SDL_FALSE);
    SDL_RenderSetScale(this->renderer, 1, 1);
    SDL_RenderClear(this->renderer);
}

SDLScreen::~SDLScreen(){
    SDL_DestroyWindow(this->window);
}

void SDLScreen::writeToBuffer(uint32_t* pixels){
    uint32_t* inactiveBuffer = this->screenBuffer1;
    if(buffer1Active){
        inactiveBuffer = this->screenBuffer2;
    }

    for(int i = 0; i < 2048; ++i){
        inactiveBuffer[i] = pixels[i];
    }

    this->buffer1Active = !this->buffer1Active;
}

void SDLScreen::open(){
    bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false; // Exit the loop when the window close button is pressed
            }
        }
    }

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    exit(1);
}

void SDLScreen::draw(){

    uint32_t* activeBuffer = this->screenBuffer1;
    if(!buffer1Active){
        activeBuffer = this->screenBuffer2;
    }

    SDL_Rect rect;
    rect.w = SCALE;
    rect.h = SCALE;
    
    for(int i = 0; i < 32; ++i){
        for(int j = 0; j < 64; ++j){

            rect.x = j*SCALE;
            rect.y = i*SCALE;
            if(activeBuffer[64*i + j]){
                SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            }
            else{
                SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(this->renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}

SDL_Window*& SDLScreen::getWindow(){
    return this->window;
}

SDL_Renderer*& SDLScreen::getRenderer(){
    return this->renderer;
}
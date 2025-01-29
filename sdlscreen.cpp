#include "sdlscreen.h"

SDLScreen::SDLScreen(){
    this->window = nullptr;
    this->renderer = nullptr;
}

SDLScreen::~SDLScreen(){
    SDL_DestroyWindow(this->window);
}

void SDLScreen::open(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &this->window, &this->renderer);
    SDL_SetWindowResizable(this->window, SDL_FALSE);
    SDL_RenderSetScale(this->renderer, 1, 1);

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    SDL_Rect rect;
    rect.x = 250;
    rect.y = 150;
    rect.w = 200;
    rect.h = 200;

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(this->renderer, &rect);

    SDL_RenderPresent(renderer);
    
    bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false; // Exit the loop when the window close button is pressed
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
#include "sdlscreen.h"

SDLScreen::SDLScreen(Chip8* ch8){
    this->ch8 = ch8;
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

void SDLScreen::writeToBuffer(bool* pixels){
    bool* inactiveBuffer = this->screenBuffer1;
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
            this->handleKeyPress(event);
        }
    }

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    exit(0);
}

void SDLScreen::handleKeyPress(SDL_Event& event){
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_1: std::cout << "1 is down" << std::endl; this->ch8->inputKeys[0] = 1; break;
            case SDLK_2: std::cout << "2 is down" << std::endl; this->ch8->inputKeys[1] = 1; break;
            case SDLK_3: std::cout << "3 is down" << std::endl; this->ch8->inputKeys[2] = 1; break;
            case SDLK_4: std::cout << "C is down" << std::endl; this->ch8->inputKeys[3] = 1; break;
            case SDLK_q: std::cout << "4 is down" << std::endl; this->ch8->inputKeys[4] = 1; break;
            case SDLK_w: std::cout << "5 is down" << std::endl; this->ch8->inputKeys[5] = 1; break;
            case SDLK_e: std::cout << "6 is down" << std::endl; this->ch8->inputKeys[6] = 1; break;
            case SDLK_r: std::cout << "D is down" << std::endl; this->ch8->inputKeys[7] = 1; break;
            case SDLK_a: std::cout << "7 is down" << std::endl; this->ch8->inputKeys[8] = 1; break;
            case SDLK_s: std::cout << "8 is down" << std::endl; this->ch8->inputKeys[9] = 1; break;
            case SDLK_d: std::cout << "9 is down" << std::endl; this->ch8->inputKeys[10] = 1; break;
            case SDLK_f: std::cout << "E is down" << std::endl; this->ch8->inputKeys[11] = 1; break;
            case SDLK_z: std::cout << "A is down" << std::endl; this->ch8->inputKeys[12] = 1; break;
            case SDLK_x: std::cout << "0 is down" << std::endl; this->ch8->inputKeys[13] = 1; break;
            case SDLK_c: std::cout << "B is down" << std::endl; this->ch8->inputKeys[14] = 1; break;
            case SDLK_v: std::cout << "F is down" << std::endl; this->ch8->inputKeys[15] = 1; break;
        }
    }
    if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
            case SDLK_1: std::cout << "1 is up" << std::endl; this->ch8->inputKeys[0] = 0; break;
            case SDLK_2: std::cout << "2 is up" << std::endl; this->ch8->inputKeys[1] = 0; break;
            case SDLK_3: std::cout << "3 is up" << std::endl; this->ch8->inputKeys[2] = 0; break;
            case SDLK_4: std::cout << "C is up" << std::endl; this->ch8->inputKeys[3] = 0; break;
            case SDLK_q: std::cout << "4 is up" << std::endl; this->ch8->inputKeys[4] = 0; break;
            case SDLK_w: std::cout << "5 is up" << std::endl; this->ch8->inputKeys[5] = 0; break;
            case SDLK_e: std::cout << "6 is up" << std::endl; this->ch8->inputKeys[6] = 0; break;
            case SDLK_r: std::cout << "D is up" << std::endl; this->ch8->inputKeys[7] = 0; break;
            case SDLK_a: std::cout << "7 is up" << std::endl; this->ch8->inputKeys[8] = 0; break;
            case SDLK_s: std::cout << "8 is up" << std::endl; this->ch8->inputKeys[9] = 0; break;
            case SDLK_d: std::cout << "9 is up" << std::endl; this->ch8->inputKeys[10] = 0; break;
            case SDLK_f: std::cout << "E is up" << std::endl; this->ch8->inputKeys[11] = 0; break;
            case SDLK_z: std::cout << "A is up" << std::endl; this->ch8->inputKeys[12] = 0; break;
            case SDLK_x: std::cout << "0 is up" << std::endl; this->ch8->inputKeys[13] = 0; break;
            case SDLK_c: std::cout << "B is up" << std::endl; this->ch8->inputKeys[14] = 0; break;
            case SDLK_v: std::cout << "F is up" << std::endl; this->ch8->inputKeys[15] = 0; break;
        }
    }
}

void SDLScreen::draw(){

    bool* activeBuffer = this->screenBuffer1;
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
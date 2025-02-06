#include "eventhandler.h"

EventHandler::EventHandler(Chip8* ch8, SDL_Event* event){
    this->ch8 = ch8;
    this->event = event;

    //sounds
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    this->sound = Mix_LoadWAV("beep-02.wav");
}

void EventHandler::handleQuitEvent(){
    if(this->event->type == SDL_QUIT){
        exit(0);
    }
}

void EventHandler::handleKeyEvent(){
    int keyPressCooldown = 30;
    if(this->event->type == SDL_KEYDOWN){
        switch(this->event->key.keysym.sym){
            case SDLK_1: std::cout << "1 key is down" << std::endl; this->ch8->inputKeys[0] = keyPressCooldown; break;
            case SDLK_2: std::cout << "2 key is down" << std::endl; this->ch8->inputKeys[1] = keyPressCooldown; break;
            case SDLK_3: std::cout << "3 key is down" << std::endl; this->ch8->inputKeys[2] = keyPressCooldown; break;
            case SDLK_4: std::cout << "C key is down" << std::endl; this->ch8->inputKeys[3] = keyPressCooldown; break;
            case SDLK_q: std::cout << "4 key is down" << std::endl; this->ch8->inputKeys[4] = keyPressCooldown; break;
            case SDLK_w: std::cout << "5 key is down" << std::endl; this->ch8->inputKeys[5] = keyPressCooldown; break;
            case SDLK_e: std::cout << "6 key is down" << std::endl; this->ch8->inputKeys[6] = keyPressCooldown; break;
            case SDLK_r: std::cout << "D key is down" << std::endl; this->ch8->inputKeys[7] = keyPressCooldown; break;
            case SDLK_a: std::cout << "7 key is down" << std::endl; this->ch8->inputKeys[8] = keyPressCooldown; break;
            case SDLK_s: std::cout << "8 key is down" << std::endl; this->ch8->inputKeys[9] = keyPressCooldown; break;
            case SDLK_d: std::cout << "9 key is down" << std::endl; this->ch8->inputKeys[10] = keyPressCooldown; break;
            case SDLK_f: std::cout << "E key is down" << std::endl; this->ch8->inputKeys[11] = keyPressCooldown; break;
            case SDLK_z: std::cout << "A key is down" << std::endl; this->ch8->inputKeys[12] = keyPressCooldown; break;
            case SDLK_x: std::cout << "0 key is down" << std::endl; this->ch8->inputKeys[13] = keyPressCooldown; break;
            case SDLK_c: std::cout << "B key is down" << std::endl; this->ch8->inputKeys[14] = keyPressCooldown; break;
            case SDLK_v: std::cout << "F key is down" << std::endl; this->ch8->inputKeys[15] = keyPressCooldown; break;
        }
    }
}

void EventHandler::handleSoundEvent(){
    if(this->ch8->soundTimer >= 0){
        Mix_PlayChannel(-1, this->sound, 0);
    }
}

void EventHandler::handleEvents(){
    while(SDL_PollEvent(&(*this->event))){
        this->handleQuitEvent();
        this->handleKeyEvent();
        this->handleSoundEvent();
    }
}
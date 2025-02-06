#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include "chip8.h"

class EventHandler{
private:
    Chip8* ch8;
    SDL_Event* event;
    Mix_Chunk* sound;

public:
    EventHandler(Chip8* ch8, SDL_Event* event);
    void handleQuitEvent();
    void handleKeyEvent();
    void handleSoundEvent();
    void handleEvents();
};


#endif
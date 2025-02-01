#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>
#include "chip8.h"

class EventHandler{
private:
    Chip8* ch8;
    SDL_Event* event;

public:
    EventHandler(Chip8* ch8, SDL_Event* event);
    void handleQuitEvent();
    void handleKeyEvent();
    void handleEvents();
};


#endif
#ifndef SDLSCREEN_H
#define SDLSCREEN_H

#define SCALE 15
#define SCREEN_WIDTH 64*SCALE
#define SCREEN_HEIGHT 32*SCALE

#include <SDL2/SDL.h>
#include <iostream>

class SDLScreen{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    uint32_t screenBuffer1[64 * 32];
    uint32_t screenBuffer2[64 * 32];

public:
    SDLScreen();
    ~SDLScreen();
    void open();
    void draw();
    void writeToBuffer(uint32_t* pixels);
};

#endif
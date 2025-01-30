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
    uint32_t screenBuffer1[64 * 32] = {0};
    uint32_t screenBuffer2[64 * 32] = {0};
    bool buffer1Active = true;

public:
    SDLScreen();
    ~SDLScreen();
    void writeToBuffer(uint32_t* pixels);
    void draw();
    void open();

    SDL_Window*& getWindow();
    SDL_Renderer*& getRenderer();
};

#endif
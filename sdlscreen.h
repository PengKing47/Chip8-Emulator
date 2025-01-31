#ifndef SDLSCREEN_H
#define SDLSCREEN_H

#define SCALE 15
#define SCREEN_WIDTH 64*SCALE
#define SCREEN_HEIGHT 32*SCALE

#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include "chip8.h"
#include "opdecoder.h"

class SDLScreen{
private:
    Chip8* ch8;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool screenBuffer1[64 * 32] = {0};
    bool screenBuffer2[64 * 32] = {0};
    bool buffer1Active = true;

public:
    SDLScreen(Chip8* ch8);
    ~SDLScreen();
    void writeToBuffer(bool* pixels);
    void draw();
    void open();
    void handleKeyPress(SDL_Event& event);

    SDL_Window*& getWindow();
    SDL_Renderer*& getRenderer();
};

#endif
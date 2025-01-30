#ifndef CHIP8_H
#define CHIP8_H

#define START_ADDRESS 0x200
#define FONT_SIZE 80
#define FONT_START_ADDRESS 0x050

#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include "sdlscreen.h"

class Chip8{
private:
    uint8_t registers[16];
    uint8_t memory[4096];
    uint16_t indexRegister;
    uint16_t programCounter;
    uint16_t stack[16];
    uint8_t stackPointer;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t inputKeys[16];
    uint32_t pixels[64 * 32] = {0};
    uint16_t opcode;

public:
    Chip8();
    void loadRom(const std::string& filename);
    void loadFonts();
    void start();
    void updateTimers();
    friend std::ostream& operator<<(std::ostream& stream, const Chip8& ch8);

    friend class OpDecoder;
    friend class SDLScreen;
};

#endif

#ifndef CHIP8_H
#define CHIP8_H

#define START_ADDRESS 0x200
#define FONT_SIZE 80
#define FONT_START_ADDRESS 0x50

#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

class Chip8{
private:
    uint8_t registers[16] = {0};
    uint8_t memory[4096] = {0};
    uint16_t indexRegister;
    uint16_t programCounter;
    uint16_t stack[16] = {0};
    uint8_t stackPointer;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t inputKeys[16] = {0};
    bool pixels[64 * 32] = {0};
    uint16_t opcode;

public:
    Chip8();
    void loadRom(const std::string& filename);
    void loadFonts();
    void start(uint8_t bitFlags);
    void updateTimers();
    void clearInput();
    friend std::ostream& operator<<(std::ostream& stream, const Chip8& ch8);

    friend class OpDecoder;
    friend class SDLScreen;
    friend class EventHandler;
};

#endif

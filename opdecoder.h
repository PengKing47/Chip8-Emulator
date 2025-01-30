#ifndef OPDECODER_H
#define OPDECODER_H

#include "chip8.h"

class OpDecoder{
private:
    Chip8* ch8;

public:
    OpDecoder(Chip8* ch8);
    void fetch();
    void execute();

    //commands
    void clearScreen();
    void jump();
    void setRegister();
    void add();
    void setIndexRegister();
    void display();
};

#endif
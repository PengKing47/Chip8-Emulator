#ifndef OPDECODER_H
#define OPDECODER_H

#include <cstdlib>
#include "chip8.h"

class OpDecoder{
private:
    Chip8* ch8;

public:
    OpDecoder(Chip8* ch8);
    void fetch();
    void execute();

    //instructions
    void clearScreen();
    void jump();
    void setRegister();
    void add();
    void setIndexRegister();
    void display();
    void call();
    void ret();
    void skipRegValE();
    void skipRegValNE();
    void skipRegRegE();
    void skipRegRegNE();
    void jumpWithOffset();
    void getRandom();
    void set();
    void binaryOr();
    void binaryAnd();
    void LogicalXor();
    void addReg();
    void subtract();
    void subtractReversed();
    void shiftRight();
    void shiftLeft();
};

#endif
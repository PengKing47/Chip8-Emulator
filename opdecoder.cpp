#include "opdecoder.h"

OpDecoder::OpDecoder(Chip8* ch8){
    this->ch8 = ch8;
}

void OpDecoder::fetch(){
    Chip8& chip = *(this->ch8);
    chip.opcode = (chip.memory[chip.programCounter] << 8) | chip.memory[chip.programCounter+1];
    chip.programCounter += 2;
}

void OpDecoder::execute(){
    uint16_t opcode = this->ch8->opcode;
    int n1 = opcode >> 12; // get the first nibble

    switch(n1){
        case 0x00E0: clearScreen(); break;
        case 0x1: jump(); break;
        case 0x6: setRegister(); break;
        case 0x7: add(); break;
        case 0xA: setIndexRegister(); break;
        case 0xD: display(); break;
    }
}

void OpDecoder::clearScreen(){
    for(int i = 0; i < 2048; ++i){
        this->ch8->pixels[i] = 0;
    }
}

void OpDecoder::jump(){
    uint16_t opcode = this->ch8->opcode;
    this->ch8->programCounter = opcode & 0xFFF;
}

void OpDecoder::setRegister(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t value = opcode & 0xFF;
    this->ch8->registers[n2] = value;
}

void OpDecoder::add(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t value = opcode & 0xFF;
    this->ch8->registers[n2] += value;
}

void OpDecoder::setIndexRegister(){
    uint16_t opcode = this->ch8->opcode;
    this->ch8->indexRegister = opcode & 0xFFF;
}

void OpDecoder::display(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    uint8_t n4 = opcode & 0xF;

    int x = this->ch8->registers[n2] % 64;
    int y = this->ch8->registers[n3] % 32;
    this->ch8->registers[15] = 0; // VF register

    for(int i = 0; i < n4; i++){
        uint8_t spriteData = this->ch8->memory[this->ch8->indexRegister + i];
        int tempX = x;
        //iterating through the 8 bit int
        for(int j = 7; j >= 0; --j){
            if(tempX >= 64){
                break;
            }
            bool on = (spriteData >> j) & 0x01;
            int location = (y)*64 + tempX;
            if(on && this->ch8->pixels[location]){
                this->ch8->pixels[location] = 0;
                this->ch8->registers[15] = 1;
            }
            else if(on){
                this->ch8->pixels[location] = 1;
            } 
            ++tempX;
        }

        ++y;
        if(y >= 32){
            break;
        }
    }
}
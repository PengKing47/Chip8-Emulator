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
    }
}

void OpDecoder::clearScreen(){
    //TODO
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
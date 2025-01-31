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
    uint8_t n1 = opcode >> 12;
    uint8_t n4 = opcode & 0xF;
    uint8_t lsb = opcode & 0xFF;

    switch(n1){
        case 0x0: 
            switch(opcode){
                case 0x00E0: clearScreen(); return;
                case 0x00EE: ret(); return;
            }
        case 0x1: jump(); return;
        case 0x2: call(); return;
        case 0x3: skipRegValE(); return;
        case 0x4: skipRegValNE(); return;
        case 0x5: skipRegRegE(); return;
        case 0x6: setRegister(); return;
        case 0x7: add(); return;
        case 0x8: 
            switch(n4){
                case 0x0: set(); return;
                case 0x1: binaryOr(); return;
                case 0x2: binaryAnd(); return;
                case 0x3: LogicalXor(); return;
                case 0x4: addReg(); return;
                case 0x5: subtract(); return;
                case 0x6: shiftRight(); return;
                case 0x7: subtractReversed(); return;     
                case 0xE: shiftLeft(); return;
            }
        case 0x9: skipRegRegNE(); return;
        case 0xA: setIndexRegister(); return;
        case 0xB: jumpWithOffset(); return;
        case 0xC: getRandom(); return;
        case 0xD: display(); return;
        case 0xF:
            switch(lsb){
                case 0x07: getDelayTimer(); return;
                case 0x0A: getKey(); return;
                case 0x15: setDelayTimer(); return;
                case 0x18: setSoundTimer(); return;
                case 0x1E: addToIndex(); return;
                case 0x29: fontCharacter(); return;
                case 0x33: binaryDecimalConversion(); return;
                case 0x55: storeMemory(); return;
                case 0x65: loadMemory(); return;
            }
        default: std::cerr << "Unknown opcode: " << std::hex << opcode << std::dec << std::endl; return;
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

void OpDecoder::call(){
    uint16_t opcode = this->ch8->opcode;
    this->ch8->stack[this->ch8->stackPointer] = this->ch8->programCounter;
    --this->ch8->stackPointer;
    this->ch8->programCounter = opcode & 0xFFF;
}

void OpDecoder::ret(){
    ++this->ch8->stackPointer;
    this->ch8->programCounter = this->ch8->stack[this->ch8->stackPointer];
    this->ch8->stack[this->ch8->stackPointer] = 0x0;
}

void OpDecoder::skipRegValE(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t val = opcode & 0xFF;
    if(this->ch8->registers[n2] == val){
        ++this->ch8->programCounter;
    }
}

void OpDecoder::skipRegValNE(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t val = opcode & 0xFF;
    if(this->ch8->registers[n2] != val){
        ++this->ch8->programCounter;
    }
}

void OpDecoder::skipRegRegE(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    if(this->ch8->registers[n2] == this->ch8->registers[n3]){
        ++this->ch8->programCounter;
    }
}

void OpDecoder::skipRegRegNE(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    if(this->ch8->registers[n2] != this->ch8->registers[n3]){
        ++this->ch8->programCounter;
    }
}

//ambiguous instructions - only one implemeted rn
void OpDecoder::jumpWithOffset(){
    uint16_t opcode = this->ch8->opcode;
    int address = (opcode & 0xFFF) + this->ch8->registers[0];
    this->ch8->programCounter = address;
}

void OpDecoder::getRandom(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t val = opcode & 0xFF;
    uint8_t random = rand() % 256;
    this->ch8->registers[n2] = random & val;
}

void OpDecoder::set(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    this->ch8->registers[n2] = this->ch8->registers[n3];
}

void OpDecoder::binaryOr(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    this->ch8->registers[n2] = this->ch8->registers[n2] | this->ch8->registers[n3];
}

void OpDecoder::binaryAnd(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    this->ch8->registers[n2] = this->ch8->registers[n2] & this->ch8->registers[n3];
}

void OpDecoder::LogicalXor(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    this->ch8->registers[n2] = this->ch8->registers[n2] ^ this->ch8->registers[n3];
}

void OpDecoder::addReg(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    if(this->ch8->registers[n2] + this->ch8->registers[n3] > 0xFF){
        this->ch8->registers[15] = 1;
    }else{
        this->ch8->registers[15] = 0;
    }
    this->ch8->registers[n2] += this->ch8->registers[n3];
}

void OpDecoder::subtract(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    if(this->ch8->registers[n2] > this->ch8->registers[n3]){
        this->ch8->registers[15] = 1;
    }else{
        this->ch8->registers[15] = 0;
    }
    this->ch8->registers[n2] -= this->ch8->registers[n3];
}

void OpDecoder::subtractReversed(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    if(this->ch8->registers[n2] > this->ch8->registers[n3]){
        this->ch8->registers[15] = 1;
    }else{
        this->ch8->registers[15] = 0;
    }
    this->ch8->registers[n2] = this->ch8->registers[n3] - this->ch8->registers[n2];
}  

//ambiguous instructions - only one implemeted rn
void OpDecoder::shiftRight(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    this->ch8->registers[n2] = this->ch8->registers[n3];
    this->ch8->registers[15] = this->ch8->registers[n2] & 0x1;
    this->ch8->registers[n2] >>= 1;
}

//ambiguous instructions - only one implemeted rn
void OpDecoder::shiftLeft(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t n3 = (opcode >> 4) & 0xF;
    this->ch8->registers[n2] = this->ch8->registers[n3];
    this->ch8->registers[15] = this->ch8->registers[n2] >> 7;
    this->ch8->registers[n2] <<= 1;
}

void OpDecoder::getDelayTimer(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    this->ch8->registers[n2] = this->ch8->delayTimer;
}

void OpDecoder::setDelayTimer(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    this->ch8->delayTimer = this->ch8->registers[n2];
}

void OpDecoder::setSoundTimer(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    this->ch8->soundTimer = this->ch8->registers[n2];
}

void OpDecoder::addToIndex(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    this->ch8->indexRegister += this->ch8->registers[n2];
}

void OpDecoder::getKey(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    for(int i = 0; i <= 0xF; ++i){
        if(this->ch8->inputKeys[i]){
            this->ch8->registers[n2] = i;
            return;
        }
    }
    this->ch8->programCounter -= 2;
}

void OpDecoder::binaryDecimalConversion(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    uint8_t val = this->ch8->registers[n2];
    this->ch8->memory[this->ch8->indexRegister+2] = val%10;
    val/=10;
    this->ch8->memory[this->ch8->indexRegister+1] = val%10;
    val/=10;
    this->ch8->memory[this->ch8->indexRegister] = val%10;
}

void OpDecoder::storeMemory(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    for(int i = 0; i <= n2; ++i){
        this->ch8->memory[this->ch8->indexRegister+i] = this->ch8->registers[i];
    }
}

void OpDecoder::loadMemory(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    for(int i = 0; i <= n2; ++i){
        this->ch8->registers[i] = this->ch8->memory[this->ch8->indexRegister+i];
    }
}

void OpDecoder::fontCharacter(){
    uint16_t opcode = this->ch8->opcode;
    uint8_t n2 = (opcode >> 8) & 0xF;
    this->ch8->indexRegister = FONT_START_ADDRESS + (this->ch8->registers[n2]*5);
}
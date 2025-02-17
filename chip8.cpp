#include "chip8.h"
#include "opdecoder.h"
#include "sdlscreen.h"
#include "eventhandler.h"

Chip8::Chip8(){
    this->programCounter = START_ADDRESS;
    this->stackPointer = 0xF;
    this->loadFonts();
}

void Chip8::loadRom(const std::string& filename){
    std::ifstream infile(filename, std::ios::binary);
    if(!infile.is_open()){
        std::cerr << "Could not open file " << filename << '\n';
        exit(1);
    }

    int currentAddress = START_ADDRESS;
    char byte;  // Read 1 byte at a time

    while (infile.get(byte)) {  // Read the first byte
        this->memory[currentAddress] = static_cast<uint8_t>(byte);  

        if (infile.get(byte)) {  // Read the second byte
            this->memory[currentAddress+1] = static_cast<uint8_t>(byte);
        }
        currentAddress += 2;
    }

    infile.close();
    std::cout << "ROM loaded scuessfully" << '\n';
}

void Chip8::loadFonts(){
    uint8_t fonts[FONT_SIZE] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for(int i = 0; i < FONT_SIZE; ++i){
        this->memory[FONT_START_ADDRESS + i] = fonts[i];
    }
}

void Chip8::start(uint8_t bitFlags){
    OpDecoder opDecoder(this, bitFlags);
    SDLScreen screen(this);
    SDL_Event event;
    EventHandler eventHandler(this, &event);
    while(true){
        eventHandler.handleEvents();
        opDecoder.fetch();
        std::cout << "0x" << std::hex << (int)this->opcode << std::endl;
        opDecoder.execute();
        screen.writeToBuffer(this->pixels);
        screen.draw();
        this->updateTimers();
        this->clearInput();
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // 16 is roughly 60 hz
    }
}

void Chip8::updateTimers(){
    if(this->delayTimer > 0){
        --this->delayTimer;
    }
    if(this->soundTimer > 0){
        --this->soundTimer;
    }
}

std::ostream& operator<<(std::ostream& stream, const Chip8& ch8){
    for (int i = 0; i < 4096; i++) {
        stream << "0x" << std::hex << (int)ch8.memory[i] << " ";  // print memory as hex
        if ((i + 1) % 16 == 0) {  // line break after every 16 bytes
            stream << '\n';
        }
    }
    return stream;
}

void Chip8::clearInput(){
    for(int i = 0; i <= 0xF; ++i){
        if(this->inputKeys[i] > 0){
            --this->inputKeys[i];
        }
    }
}
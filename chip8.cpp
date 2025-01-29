#include "chip8.h"
#include "sdlscreen.h"

Chip8::Chip8(){
    SDLScreen screen;
    screen.open();
    this->programCounter = START_ADDRESS;
    this->loadFonts();
}

void Chip8::loadRom(const std::string& filename){
    std::ifstream infile(filename, std::ios::binary);
    if(!infile.is_open()){
        std::cerr << "Could not open file " << filename << '\n';
        exit(1);
    }
    int currentAdress = START_ADDRESS;
    uint16_t opcode;
    while(infile.read(reinterpret_cast<char*>(&opcode), sizeof(opcode))){
        uint8_t msb = opcode >> 8;
        uint8_t lsb = opcode & 0xFF;
        this->memory[currentAdress] = msb;
        this->memory[currentAdress+1] = lsb;
        currentAdress += 2;
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

std::ostream& operator<<(std::ostream& stream, const Chip8& ch8){
    for (int i = 0; i < 4096; i++) {
        stream << "0x" << std::hex << (int)ch8.memory[i] << " ";  // print memory as hex
        if ((i + 1) % 16 == 0) {  // line break after every 16 bytes
            stream << '\n';
        }
    }
    return stream;
}

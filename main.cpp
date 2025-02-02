#include "chip8.h"

int main(int argc, char** argv){
    if(argc != 2 && argc != 3){
        std::cerr << "ERROR: Usage: " << argv[0]  << " rom_file.txt optional-flags(00, 01, 10, 11)" << std::endl;
        exit(1);
    }
    Chip8 ch8;
    ch8.loadRom(argv[1]);
    /*
    4 bit bit flag - 0x00(00) - 0x01(01) - 0x02(10) - 0x03(11)
    msb = offset jump flag - 1: jump + v0 - 0: jump + VX
    lsb = bit shift flag - 1: VY is not modified - 0: VY is modified
    */
    uint8_t bitFlags;
    if(argv[2] == "00"){
        bitFlags = 0x0;
    }else if(argv[2] == "01"){
        bitFlags = 0x1;
    }else if(argv[2] == "10"){
        bitFlags = 0x2;
    }else{
        bitFlags = 0x3;
    }

    //std::cout << ch8 << std::endl;
    ch8.start(bitFlags);
}
#include "chip8.h"

int main(){
    Chip8 ch8;
    ch8.loadRom("roms/Pong.ch8");
    /*
    4 bit bit flah - 0x00(00) - 0x01(01) - 0x02(10) - 0x03(11)
    msb = offset jump flag - 1: jump + v0 - 0: jump + VX
    lsb = bit shift flag - 1: VY is not modified - 0: VY is modified
    */
    uint8_t bitFlag = 0x00;

    std::cout << ch8 << std::endl;
    ch8.start();
}   
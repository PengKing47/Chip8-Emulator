#include "sdlscreen.h"
#include "chip8.h"

int main(){
    Chip8 ch8;
    ch8.loadRom("roms/ibm.ch8");
    ch8.start();
    //std::cout << ch8 << std::endl;
}   
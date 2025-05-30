#include "chip8.hpp"
#include <fstream>

Chip8::Chip8(){
    pc = START_ADDRESS;
    
    for (long i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_ADDRESS + i] = FONTSET[i];
    }
};

void Chip8::LoadROM(char const* filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (file.is_open()){
            // get size of file and allocate 
            std::streampos size = file.tellg();
            char* buffer = new char[size];

            file.seekg(0, std::ios::beg);
            file.read(buffer, size);
            file.close();

            // load rom contents into memory starting at 0x200
            for (long i = 0; i < size; i++){
                memory[START_ADDRESS + i] = buffer[i];
            }
            delete[] buffer;
        }
    }

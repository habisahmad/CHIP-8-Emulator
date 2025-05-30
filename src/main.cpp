#include <iostream>
#include <cstdint>
#include <fstream>
using namespace std;

class Chip8 {
    public:
        uint8_t memory[4096]{}; // 4KB memory
        uint8_t video[64*32]{}; // Display
        uint16_t pc{}; // Program Counter
        uint8_t delaytimer{}; // Delay Timer
        uint8_t soundTimer{}; // Sound Timer
        uint16_t stack[16]{}; // Stack
        uint8_t stackptr{};
        uint8_t V[16]{}; // General purpose registers (V0-VF)
        uint16_t opcode;

    // Instructions from the ROM will be stored starting at 0x200,
    const unsigned int START_ADRESS = 0x200;
    // Load ROM instructions to emulator
    void Chip8::LoadROM(char const* filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (file.is_open()){
            // get size of file and allocate 
            std:streampos size = file.tellg();
            char* buffer = new char[size];

            file.seekg(0, std::ios::beg);
            file.read(buffer, size);
            file.close();

            // load rom contents starting at 0x200
            for (long i = 0; i < size; i++){
                memory[START_ADRESS + i] = buffer[i];
            }
            delete[] buffer;
        }
    }
};
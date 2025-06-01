#include "chip8.hpp"
#include <fstream>
#include <chrono>
#include <random>


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

uint8_t Chip8::RandGen(){
    uint8_t v1 = rand() % 256;
    uint16_t NNN = opcode & 0x0FFF;
    v1 = v1 & NNN;
    return v1;
}

void Chip8::OP_00E0(){
    for (int i = 0; i < 64*32; i++){
        video[i] = 0;
    }
}

void Chip8::OP_1NNN(){
    uint16_t NNN = opcode & 0x0FFF; // drop first 4 bits of instruction 
    pc = NNN;
}

// Call & return from subroutines
void Chip8::OP_2NNN(){
    uint16_t NNN = opcode & 0x0FFF; // drop first 4 bits of instruction 
    stack[stackptr] = pc;
    ++stackptr;
    pc = NNN;
}

void Chip8::OP_00EE(){
    --stackptr;
    pc = stack[stackptr];
}

void Chip8::OP_3XNN(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t NN = opcode & 0x00FFu;

    if (V[Vx] == NN) {
        pc += 2;
    }
}

void Chip8::OP_4XNN(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t NN = opcode & 0x00FFu;

    if (V[Vx] != NN) {
        pc += 2;
    }
}

void Chip8::OP_9XY0(){
    uint8_t Vx = (opcode & 0x0F00) >> 8; // shift by 8 bits
    uint8_t Vy = (opcode & 0x00FFu) >> 4;

    if (V[Vx] != V[Vy]) {
        pc += 2;
    }
}

void Chip8::OP_5XY0(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00FF) >> 4;

    if (V[Vx] == V[Vy]) {
        pc += 2;
    }
}

void Chip8::OP_6XNN(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    V[Vx] = opcode & 0x00FF;
}

void Chip8::OP_7XNN(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t NN = opcode & 0x00FF;

    V[Vx] += NN;
}

void Chip8::OP_8XY0(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    V[Vx] = V[Vy];
}

void Chip8::OP_8XY1() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    V[Vx] = V[Vx] | V[Vy];

}

void Chip8::OP_8XY2() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    V[Vx] = V[Vx] & V[Vy];

}

void Chip8::OP_8XY3() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    V[Vx] = V[Vx] ^ V[Vy];
}

void Chip8::OP_8XY4() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    uint16_t sum = V[Vx] + V[Vy];

    // Check if overflow on sum, trigger carry flag (VF)
    if (sum > 255) {
        V[15] = 1;
    }
    else {
        V[15] = 0;
    }
    V[Vx] = sum & 0xFF; // Keep lower 8 bits
}


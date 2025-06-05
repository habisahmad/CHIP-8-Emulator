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

void Chip8::OP_8XY5() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    if (V[Vx] > V[Vy]) {
        V[15] = 0;
    }
    else {
        V[15] = 1;
    }

    V[Vx] = V[Vx] - V[Vy];
}

void Chip8::OP_8XY7() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    if (V[Vy] > V[Vx]) {
        V[15] = 0;
    }
    else {
        V[15] = 1;
    }

    V[Vx] = V[Vy] - V[Vx];
}

void Chip8::OP_8XY6(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    V[Vx] = V[Vy];
    if ((V[Vx] & 1) == 1) {
        V[15] = 1;
    }
    else {
        V[15] = 0;
    }
    V[Vx] = V[Vx] >> 1;

}

void Chip8::OP_8XYE(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    V[Vx] = V[Vy];
    if ((V[Vx] & 0x80) != 0) {
        V[15] = 1;
    }
    else {
        V[15] = 0;
    }
    V[Vx] = V[Vx] << 1;

}

void Chip8::OP_ANNN(){
    uint8_t NNN = (opcode & 0x0FFF);

    index = NNN;
}

void Chip8::OP_BNNN() {
    uint8_t NNN = (opcode & 0x0FFF);

    pc = NNN + V[0x0]; 
}

void Chip8::OP_CXNN() {
    uint8_t NN = opcode & 0x00FF;
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    uint8_t r = rand() % 256;

    V[Vx] = r & NN;
}

void Chip8::OP_DXYN() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    uint8_t N = opcode & 0x000F;

    // Wrap bits
    uint8_t X = V[Vx] % 64;
    uint8_t Y = V[Vy] % 32;
    V[15] = 0;

    for (unsigned int rows = 0; rows < N; rows++) {
        uint8_t spriteData = memory[index + rows];

        for (unsigned int i = 0; i < 8; i++){
            uint8_t currentPixel = spriteData & (0x80 >> i);
            
            // if current pixel is on
            if (currentPixel != 0) {
                
                if (video[(X + i) + ((Y + rows) * 64)] == 1) {
                    video[(X + i) + ((Y + rows) * 64)] = 0;
                    V[15] = 1;
                }
                video[(X + i) + ((Y + rows) * 64)] ^= 1;
            }
        }
    }
}

void Chip8::OP_EX9E(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    if (keypad[V[Vx]] == 1) {
        pc = pc + 2;
    }
}

void Chip8::OP_EXA1(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    if (keypad[V[Vx]] != 1) {
        pc = pc + 2;
    }
}

void Chip8::OP_FX07(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    V[Vx] = delaytimer;
}
void Chip8::OP_FX15(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    
    delaytimer = V[Vx];
}
void Chip8::OP_FX18(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    soundTimer = V[Vx];
}

void Chip8::OP_FX1E() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    index = index + V[Vx];
}


void Chip8::OP_FX0A() { 
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    bool keyPressed = false;

    for (unsigned int i = 0; i < 16; i++){
        if (keypad[i]){
            keyPressed = true;
            V[Vx] = i;
            break;
        }
    }

    if (!keyPressed) {
        pc = pc - 2;
    }
}

void Chip8::OP_FX29() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    index = FONTSET_ADDRESS + (5 * V[Vx]);
}

void Chip8::OP_FX33() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t num = V[Vx];

    memory[index] = num / 100;
    memory[index+1] = (num / 10) % 10;
    memory[index+2] = num % 10;
}

void Chip8::OP_FX55() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    for (int i = 0; i < Vx+1; i++){
        memory[index + i] = V[i];
    }
}

void Chip8::OP_FX65() {
    uint8_t Vx = (opcode & 0x0F00) >> 8;

    for (int i = 0; i < Vx+1; i++){
        V[i] = memory[index + i];
    }
}
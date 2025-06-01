#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>

class Chip8 {
    public:
        Chip8();
        void LoadROM(char const* filename);
        uint8_t RandGen();
        void Chip8::OP_00E0();
        void Chip8::OP_1NNN();
        void Chip8::OP_00EE();
        void Chip8::OP_2NNN();
        void Chip8::OP_3XNN();
        void Chip8::OP_4XNN();
        void Chip8::OP_5XY0();
        void Chip8::OP_9XY0();
        void Chip8::OP_6XNN();
        void Chip8::OP_7XNN();
        void Chip8::OP_8XY0();
        void Chip8::OP_8XY1();
        void Chip8::OP_8XY2();
        void Chip8::OP_8XY3();
        void Chip8::OP_8XY4();
        void Chip8::OP_8XY5();
        void Chip8::OP_8XY6();
        void Chip8::OP_8XY7();
        void Chip8::OP_8XYE();
        void Chip8::OP_ANNN();
        void Chip8::OP_BNNN();
        void Chip8::OP_CXNN();
        void Chip8::OP_DXYN();
        

    private:
        static const unsigned int START_ADDRESS = 0x200;
        static const unsigned int FONTSET_SIZE = 80;
        static const unsigned int FONTSET_ADDRESS = 0x50;
        uint8_t memory[4096]{}; // 4KB memory
        uint8_t video[64*32]{}; // Display
        uint16_t pc{}; // Program Counter
        uint8_t delaytimer{}; // Delay Timer
        uint8_t soundTimer{}; // Sound Timer
        uint16_t stack[16]{}; // Stack
        uint8_t stackptr{};
        uint8_t V[16]{}; // General purpose registers (V0-VF)
        uint16_t opcode;
        uint8_t FONTSET[FONTSET_SIZE] = {
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

};

#endif
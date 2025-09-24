#include <cstdint>


class Chip8 {
    public:
        Chip8();
        void LoadROM(char const* filename);
        void Cycle();
    
        static const unsigned int START_ADDRESS = 0x200;
        static const unsigned int FONTSET_SIZE = 80;
        static const unsigned int FONTSET_ADDRESS = 0x50;
        uint8_t memory[4096]{}; // 4KB memory
        uint32_t video[64*32]{}; // Display
        uint16_t pc{}; // Program Counter
        uint8_t delaytimer{}; // Delay Timer
        uint8_t soundTimer{}; // Sound Timer
        uint16_t stack[16]{}; // Stack
        uint8_t stackptr{};
        uint16_t index{};
        uint8_t keypad[16]{};
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

        // Functions
        void OP_00E0();
        void OP_1NNN();
        void OP_00EE();
        void OP_2NNN();
        void OP_3XNN();
        void OP_4XNN();
        void OP_5XY0();
        void OP_9XY0();
        void OP_6XNN();
        void OP_7XNN();
        void OP_8XY0();
        void OP_8XY1();
        void OP_8XY2();
        void OP_8XY3();
        void OP_8XY4();
        void OP_8XY5();
        void OP_8XY6();
        void OP_8XY7();
        void OP_8XYE();
        void OP_ANNN();
        void OP_BNNN();
        void OP_CXNN();
        void OP_DXYN();
        void OP_EX9E();
        void OP_EXA1();
        void OP_FX07();
        void OP_FX15();
        void OP_FX18();
        void OP_FX1E();
        void OP_FX0A();
        void OP_FX29();
        void OP_FX33();
        void OP_FX55();
        void OP_FX65();

        typedef void (Chip8::*Chip8Func)();
        Chip8Func table[0xF + 1];
        Chip8Func table0[0xE + 1];
        Chip8Func table8[0xE + 1];
        Chip8Func tableE[0xE + 1];
        Chip8Func tableF[0x65 + 1];

        void Table0();
        void Table8();
        void TableE();
        void TableF();

        // Do nothing
        void OP_NULL();

};
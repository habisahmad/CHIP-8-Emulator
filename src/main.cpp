#include <iostream>
#include <cstdint>
using namespace std;

uint8_t memory[4096]; // 4KB memory
uint8_t display[64][32]; // Display
uint16_t pc; // Program Counter
uint8_t delaytimer; // Delay Timer
uint8_t soundTimer; // Sound Timer
uint16_t stack[16]; // Stack
uint8_t stackptr;
uint8_t V[16]; // General purpose registers (V0-VF)



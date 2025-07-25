# CHIP-8 EMULATOR

A simple CHIP-8 Emulator built in C++ 

![image](https://github.com/user-attachments/assets/d1cd1afb-f5cc-4f8d-bbf0-b5ecb59763b2)

## Features
- Full CHIP-8 instruction set support
- OpenGL rendering using GLAD
- Sound and delay timers
- Keyboard input mapping
- Included test ROMs

## Requirements

- C++17 or later
- [CMake](https://cmake.org/) (3.10+)
- [GLAD](https://glad.dav1d.de/)
- SDL2
- pkg-config

# How to run
```bash
brew install pkg-config
brew install sdl2
git clone https://github.com/habisahmad/CHIP-8-Emulator.git
cd chip-8-emulator
mkdir build && cd build
cmake ..
make
./chip8 10 1 ../roms/ibm.ch8
```

CHIP-8 Keypad Layout    &   Keyboard Mapping
```
1 2 3 C                     1 2 3 4
4 5 6 D         --->        Q W E R
7 8 9 E                     A S D F
A 0 B F                     Z X C V
```

This emulator was created by following and learning from:

[Tobias V. Langhoff's CHIP-8 guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)

[Austin Morlan's CHIP-8 series](https://austinmorlan.com/posts/chip8_emulator/)


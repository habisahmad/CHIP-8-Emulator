A simple CHIP-8 Emulator built in C++ 

## Features
- Full CHIP-8 instruction set support
- OpenGL rendering using GLFW and GLAD
- Sound and delay timers
- Keyboard input mapping
- Included test ROMs

## Requirements

- C++17 or later
- [CMake](https://cmake.org/) (3.10+)
- [GLAD](https://glad.dav1d.de/)

# How to run
```bash
git clone https://github.com/your-username/chip8-emulator.git
cd chip8-emulator
mkdir build && cd build
cmake ..
make
./chip8 ../roms/Pong.ch8
```

CHIP-8 Keypad Layout       Keyboard Mapping

1 2 3 C                     1 2 3 4
4 5 6 D         --->        Q W E R
7 8 9 E                     A S D F
A 0 B F                     Z X C V


This emulator was created by following and learning from:

[Tobias V. Langhoff's CHIP-8 guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)

[Austin Morlan's CHIP-8 series](https://austinmorlan.com/posts/chip8_emulator/)


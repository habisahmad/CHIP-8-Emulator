# CHIP-8 EMULATOR

A simple, fast CHIP-8 emulator written in C++ with an SDL2 renderer, ported to WebAssembly via Emscripten

# Live Preview
[**▶ Play in your browser**](https://habisahmad.github.io/CHIP-8-Emulator/)
<br/>
<img width="3420" height="1520" alt="image" src="https://github.com/user-attachments/assets/f62b81ac-6f0f-45d1-bfca-d7f9a6b381d4" />

## Features
- Full CHIP-8 instruction set support
- OpenGL rendering using GLAD
- Sound and delay timers
- Keyboard input mapping
- Included test ROMs
- Lightweight HTML/CSS UI (web), deployed to GitHub Pages
## Requirements

- C++17 or later
- SDL2
- [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) (emsdk)
- 
  

# Build
```bash
em++ src/*.cpp -std=c++17 -O3 \
  -sUSE_SDL=2 \
  -sALLOW_MEMORY_GROWTH=1 \
  --preload-file roms@/roms \
  -sEXPORTED_FUNCTIONS='["_main","_loadROM"]' \
  -sEXPORTED_RUNTIME_METHODS='["cwrap","ccall","FS"]' \
  --shell-file shell.html \
  -o docs/index.html
```

## Run Locally
```bash
python3 -m http.server --directory docs 8080
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


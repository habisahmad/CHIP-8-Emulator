#include <chrono>
#include <iostream>
#include <string>
#include <emscripten.h>

#include "chip8.hpp"
#include "platform.hpp"

static int        videoScale   = 10;
static int        cycleDelayMs = 16;  
static int        videoPitch   = 0;
static bool       quit         = false;

static Platform*  platform     = nullptr;
static Chip8      chip8;
static std::chrono::high_resolution_clock::time_point g_lastCycleTime;

static double lastMs = 0.0, cpuMS = 0.0, timerMS = 0.0;
static const double CPU_HZ = 600.0;         // try 500..1000
static const double CPU_DT = 1000.0 / CPU_HZ;   // ms per CPU cycle
static const double TIMER_DT = 1000.0 / 60.0;   // ~16.6667 


static void mainloop(){
  quit = platform->ProcessInput(chip8.keypad);
  if (quit) { emscripten_cancel_main_loop(); return ; }

  const double now = emscripten_get_now();
  double time = now - lastMs; lastMs = now;
  cpuMS   += time;
  timerMS += time;

  while (cpuMS >= CPU_DT) {
    chip8.Cycle();
    cpuMS -= CPU_DT;

  while (timerMS >= TIMER_DT) {
    if (chip8.delaytimer) chip8.delaytimer--;
    if (chip8.soundTimer) chip8.soundTimer--;
    timerMS -= TIMER_DT;
  }
}
  platform->Update(chip8.video, 64 * sizeof(uint32_t));

}
int main()
{
	char const* romFilename = "/roms/Tetris.ch8";

	platform = new Platform("CHIP-8 Emulator", 64 * videoScale, 32 * videoScale, 64, 32);

	chip8.LoadROM(romFilename);
	

	videoPitch = sizeof(chip8.video[0]) * 64;

	g_lastCycleTime = std::chrono::high_resolution_clock::now();

	emscripten_set_main_loop(mainloop, 0, 1);

	return 0;
}
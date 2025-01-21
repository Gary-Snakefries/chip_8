#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <chrono>
#include "chip8.h"

int main(int argc, char** argv){
	if (argc < 2){
		std::cout << "ERROR: ROM FILENAME NOT SPECIFIED. ABORTING\n";
		return 1;
	}
	Chip8 Emulator;
	char* filename = argv[1];
	Emulator.LoadROM(filename);
	Platform platform("CHIP-8 Emulator", 64*10, 32*10, 64, 32);
	int videoPitch = sizeof(Emulator.Display[0]) * 64;
	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	while(1){
		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();
		if (dt > 4){	
			Emulator.FetchInst();
			Emulator.Execute();
			platform.Update(Emulator.Display, videoPitch);

		}
	}
	return 0;
}

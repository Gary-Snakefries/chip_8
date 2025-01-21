#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <SDL2/SDL.h>
#include "chip8.h"

Chip8::Chip8(){
	this->StackPtr = Stack;
	this->pc = START_ADDR;
	for(auto itr = 0; itr < 80; itr++){
		this->Memory[FONT_ADDR + itr] = fonts[itr];
	}
}


void Chip8::LoadROM(char* filename){
	std::ifstream romFile(filename, std::ios::binary | std::ios::ate);
	int buffSize = romFile.tellg();
	char buffer[buffSize];
	romFile.read(buffer, buffSize);
	romFile.close();
	for(auto itr = 0; itr < buffSize; itr++){
		this->Memory[START_ADDR + itr] = buffer[itr];
	}
}

void Chip8::FetchInst(){
	this->opcode = this->Memory[this->pc] << 8;
	this->opcode |= this->Memory[this->pc + 1];
	this->pc += 2;
}

void Chip8::Execute(){
	uint8_t instruction = this->opcode >> 12;
	switch(instruction){
		case 0x0:
		//std::cout << "Executing 00E0\n";
		this->ch8_00E0();
		break;

		case 0x1:
		//std::cout << "Executing 1NNN\n";
		this->ch8_1NNN();
		break;

		case 0x6:
		//std::cout << "Executing 6XNN\n";
		this->ch8_6XNN();
		break;

		case 0x7:
		//std::cout << "Executing 7XNN\n";
		this->ch8_7XNN();
		break;

		case 0xA:
		//std::cout << "Executing ANNN\n";
		this->ch8_ANNN();
		break;

		case 0xD:
		//std::cout << "Executing DXYN\n";
		this->ch8_DXYN();
		break;
		
		default:
		//std::cout << "INSTRUCTION LOST" << std::endl;
		break;
	}
}

// Code for each of the instructions
void Chip8::ch8_00E0(){
	memset(this->Display, 0, sizeof(this->Display));
}

void Chip8::ch8_1NNN(){
	this->pc = this->opcode & 0x0FFF;
}

void Chip8::ch8_6XNN(){
	this->Registers[(this->opcode & 0x0F00) >> 8] = this->opcode & 0x00FF;
}

void Chip8::ch8_7XNN(){
	this->Registers[(this->opcode & 0x0F00) >> 8] += (this->opcode & 0x00FF);
}

void Chip8::ch8_ANNN(){
	this->index = opcode & 0x0FFF;
	std::cout << this->index;
}

void Chip8::ch8_DXYN(){
	uint8_t Vx = ((this->opcode) & 0x0F00) >> 8;
	uint8_t Vy = ((this->opcode) & 0x00F0) >> 4;
	uint8_t N = (this->opcode) & 0x000F;
		
	uint8_t xCoord = (this->Registers[Vx]) % 64;
	uint8_t yCoord = (this->Registers[Vy]) % 32;
	
	this->Registers[0xF] = 0;
	
	for(unsigned int row = 0; row < N; row++){
	
		uint8_t SpriteByte = (this->Memory)[(this->index) + row];
		
		for(unsigned int col = 0; col < 8; col++){
		
			uint8_t SpritePixel = SpriteByte & (0x80 >> col);
			uint32_t* ScreenPixel = &Display[(yCoord + row) * 64 + (xCoord + col)];
			
			if(SpritePixel){
				if (*ScreenPixel == 0xFFFFFFFF){
					this->Registers[0xF] = 1;
				}
				*ScreenPixel ^= 0xFFFFFFFF;
			}
		}
	}
}


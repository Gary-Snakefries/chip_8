Requires SDL2 library to compile and run.

Compilation can be done through the command line using
"g++ main.cpp chip8.cpp -lSDL2" without the quotes.

Currently Implemented:
- Instruction 00E0
- Instruction 1NNN
- Instruction 6XNN
- Instruction 7XNN
- Instruction ANNN
- Instruction DXYN (?)

TODO:
- Resolve issues with the ibm logo test.
- Add video scaling as an option instead of hardcoding it.
- Implement the rest of the instructions.
- Implement timers, sound.
- Figure out the best cycle timing.

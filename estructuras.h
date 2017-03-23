#ifndef _STRUCTS_H_
#define _STRUCTS_H_
#define LI 50
typedef struct Program{

	int PC;
	int registers[32];
	int quantityInstructions;
	char instructions[100000][LI];
	char nameRegisters[32][7];
	
}Program;


#endif
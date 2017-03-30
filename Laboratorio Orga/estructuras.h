#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct Instruction{
	int r;
	char function[30];
	char r1[30];
	char r2[30];
	char r3[30];

}Instruction;



typedef struct Label{
	char name[30];
	int PC;
}Label;

typedef struct Program{

	int PC;
	int counterInstruction;
	int counterLabel;
	int registers[32];
	int heapMemory[100000];
	int stackMemory[100000];
	char linesControl[10];
	char nameRegisters[32][7];
	Instruction instructions[100000];
	Label labels[50000];
}Program;


#endif

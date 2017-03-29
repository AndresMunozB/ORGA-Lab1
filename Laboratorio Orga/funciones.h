#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H
Program* programInit(char *filename);
void showInstruction(Instruction instruction);
void instructionInit(Instruction* ins);
int getIndexRegister(char *strRegister,Program* program );
#endif

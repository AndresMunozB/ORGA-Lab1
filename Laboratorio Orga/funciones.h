#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H
void showInstruction(Instruction instruction);
void instructionInit(Instruction* ins);
Program* programInit(char *filename);
int getIndexRegister(char *strRegister,Program* program );
void fprintInstruction(FILE* traza,Instruction in);
void fprintRegisters(FILE* traza, Program* program);
void printRegisters(Program* program);
void exProgram(Program* program);
int getPClabel(char* label,Program* program);
void showLabels(Program* program);
void fprintTitle(FILE* traza, Program* program);
void fprintLinesControl(FILE* linesControl, Program* program);
void setLinesControl(Instruction in,Program* program);
#endif


#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(){
	Program *program= (Program*)programInit("simple.asm");
	showProgram(program);
	int i;
	for (i=0;i<program->quantityInstructions;i++){
		if(strlen(program->instructions[i])!=0){
			printf("%s\n",program->instructions[i] );
			exInstruction(program->instructions[i],program);
		}
	}


	return 0;
}
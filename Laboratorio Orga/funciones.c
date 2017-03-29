#include "estructuras.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showInstruction(Instruction instruction){
    if (instruction.r == 3){
		printf("%s %s %s %s\n",instruction.function,instruction.r1,instruction.r2,instruction.r3 );
		/*printf("%s: %d\n",instruction.function,(int)strlen(instruction.function));
		printf("%s: %d\n",instruction.r1,(int)strlen(instruction.r1));
		printf("%s: %d\n",instruction.r2,(int)strlen(instruction.r2));
		printf("%s: %d\n",instruction.r3,(int)strlen(instruction.r3));*/

    }
    if (instruction.r == 2){
        printf("%s %s %s\n",instruction.function,instruction.r1,instruction.r2);
        /*printf("%s: %d\n",instruction.function,(int)strlen(instruction.function));
		printf("%s: %d\n",instruction.r1,(int)strlen(instruction.r1));
		printf("%s: %d\n",instruction.r2,(int)strlen(instruction.r2));*/


    }
    if (instruction.r == 1){
        printf("%s %s\n",instruction.function,instruction.r1);
        /*printf("%s: %d\n",instruction.function,(int)strlen(instruction.function));
		printf("%s: %d\n",instruction.r1,(int)strlen(instruction.r1));*/
    }


	// Hola <3
}
void instructionInit(Instruction* ins){
	memset(ins->function,0,30);
	memset(ins->r1,0,30);
	memset(ins->r2,0,30);
	memset(ins->r3,0,30);
}

Program* programInit(char *filename){

	Program *program=(Program*)malloc(sizeof(Program));
	FILE* file;
	file = fopen(filename,"r");
	char buffer[40];
	program->PC=0;
	program->counterInstruction=0;
	program->counterLabel=0;
	strcpy(program->nameRegisters[0],"$zero");
	strcpy(program->nameRegisters[1],"$at");
	strcpy(program->nameRegisters[2],"$v0");
	strcpy(program->nameRegisters[3],"$v1");
	strcpy(program->nameRegisters[4],"$a0");
	strcpy(program->nameRegisters[5],"$a1");
	strcpy(program->nameRegisters[6],"$a2");
	strcpy(program->nameRegisters[7],"$a3");
	strcpy(program->nameRegisters[8],"$t0");
	strcpy(program->nameRegisters[9],"$t1");
	strcpy(program->nameRegisters[10],"$t2");
	strcpy(program->nameRegisters[11],"$t3");
	strcpy(program->nameRegisters[12],"$t4");
	strcpy(program->nameRegisters[13],"$t5");
	strcpy(program->nameRegisters[14],"$t6");
	strcpy(program->nameRegisters[15],"$t7");
	strcpy(program->nameRegisters[16],"$s0");
	strcpy(program->nameRegisters[17],"$s1");
	strcpy(program->nameRegisters[18],"$s2");
	strcpy(program->nameRegisters[19],"$s3");
	strcpy(program->nameRegisters[20],"$s4");
	strcpy(program->nameRegisters[21],"$s5");
	strcpy(program->nameRegisters[22],"$s6");
	strcpy(program->nameRegisters[23],"$s7");
	strcpy(program->nameRegisters[24],"$t8");
	strcpy(program->nameRegisters[25],"$t9");
	strcpy(program->nameRegisters[26],"$k0");
	strcpy(program->nameRegisters[27],"$k1");
	strcpy(program->nameRegisters[28],"$gp");
	strcpy(program->nameRegisters[29],"$sp");
	strcpy(program->nameRegisters[30],"$fp");
	strcpy(program->nameRegisters[31],"$ra");

	while (!feof(file)){

		memset(buffer,0,sizeof(buffer));

		fscanf(file,"%s",buffer);
		//printf("%s\n",buffer );
		if (
		!strcmp(buffer,"add") ||
		!strcmp(buffer,"addi") ||
		!strcmp(buffer,"sub") ||
		!strcmp(buffer,"subi") ||
		!strcmp(buffer,"mul") ||
		!strcmp(buffer,"div") ||
		!strcmp(buffer,"beq") ||
		!strcmp(buffer,"blt") ||
		!strcmp(buffer,"bgt")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], %[^','], %s",program->instructions[program->counterInstruction].r1,program->instructions[program->counterInstruction].r2,program->instructions[program->counterInstruction].r3);
			program->instructions[program->counterInstruction].r = 3;
			showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"lw") ||
		!strcmp(buffer,"sw")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], %[^'('](%[^')']",program->instructions[program->counterInstruction].r1,program->instructions[program->counterInstruction].r2,program->instructions[program->counterInstruction].r3);
			program->instructions[program->counterInstruction].r = 3;
			showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"la")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], (%[^')']",program->instructions[program->counterInstruction].r1,program->instructions[program->counterInstruction].r2);
			program->instructions[program->counterInstruction].r = 2;
			showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"j") ||
		!strcmp(buffer,"jal") ||
		!strcmp(buffer,"jr")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file,"%s",program->instructions[program->counterInstruction].r1);
			program->instructions[program->counterInstruction].r = 1;
			showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}

		else if (buffer[strlen(buffer)-1] == ':'){
			//printf("%s largo:%d\n", buffer,program->counterInstruction+1);
			printf("%s\n", buffer);
			strcpy(program->labels[program->counterLabel].nombre,buffer);
			program->labels[program->counterLabel].PC = program->counterInstruction+1;
			program->counterLabel++;

		}

	}

	return program;
}


int getIndexRegister(char *strRegister,Program* program ){
    int i;
    for (i=0;i<32;i++){
        if (!strcmp(program->nameRegisters[i],strRegister)){
            return i;
        }
    }
    return -1;
}




















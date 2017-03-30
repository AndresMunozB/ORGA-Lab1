#include "estructuras.h"
#include "mips.h"
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
    int i;
    for (i=0;i<32;i++){
        program->registers[i] = 0;
    }
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
			fscanf(file," %[^','], %[^','], %s\n",program->instructions[program->counterInstruction].r1,program->instructions[program->counterInstruction].r2,program->instructions[program->counterInstruction].r3);
			program->instructions[program->counterInstruction].r = 3;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;
			//printf("%d\n",program->counterInstruction);

		}
		else if (
		!strcmp(buffer,"lw") ||
		!strcmp(buffer,"sw")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], %[^'('](%[^')']",program->instructions[program->counterInstruction].r1,program->instructions[program->counterInstruction].r2,program->instructions[program->counterInstruction].r3);
			program->instructions[program->counterInstruction].r = 3;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"la")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], (%[^')']",program->instructions[program->counterInstruction].r1,program->instructions[program->counterInstruction].r2);
			program->instructions[program->counterInstruction].r = 2;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"j") ||
		!strcmp(buffer,"jal") ||
		!strcmp(buffer,"jr")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %s\n",program->instructions[program->counterInstruction].r1);
			program->instructions[program->counterInstruction].r = 1;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}

		else if (buffer[strlen(buffer)-1] == ':'){
			//printf("%s largo:%d\n", buffer,program->counterInstruction);
			//printf("%s\n", buffer);
			buffer[strlen(buffer)-1] = '\0';
			strcpy(program->labels[program->counterLabel].name,buffer);
			program->labels[program->counterLabel].PC = program->counterInstruction;
			program->counterLabel++;
			//printf("%d\n",program->counterLabel);


		}

	}

	return program;
}


int getIndexRegister(char *strRegister,Program* program ){
    //printf("Entrada:%s:\n",strRegister);
    int i;
    for (i=0;i<32;i++){
        //printf("%s:\n",program->nameRegisters[i]);
        if (!strcmp(program->nameRegisters[i],strRegister)){
                //printf("ENTRE IF: %d\n",i);
            return i;
        }
    }
    return -1;
}
void fprintInstruction(FILE* traza,Instruction in){
    if (
		!strcmp(in.function,"add") ||
		!strcmp(in.function,"addi") ||
		!strcmp(in.function,"sub") ||
		!strcmp(in.function,"subi") ||
		!strcmp(in.function,"mul") ||
		!strcmp(in.function,"div") ||
		!strcmp(in.function,"beq") ||
		!strcmp(in.function,"blt") ||
		!strcmp(in.function,"bgt")
		){
            fprintf(traza,"%s %s, %s, %s:\n", in.function,in.r1,in.r2,in.r3);
    }
    else if (
		!strcmp(in.function,"lw") ||
		!strcmp(in.function,"sw")
		){
		    fprintf(traza,"%s %s, %s(%s):\n", in.function,in.r1,in.r2,in.r3);
    }
    else if (
		!strcmp(in.function,"la")
		){
		    fprintf(traza,"%s %s, (%s):\n", in.function,in.r1,in.r2);
    }
    else if (
		!strcmp(in.function,"j") ||
		!strcmp(in.function,"jal") ||
		!strcmp(in.function,"jr")
		){
		    fprintf(traza,"%s %s:\n", in.function,in.r1);
    }
}
void fprintRegisters(FILE* traza, Program* program){
    int i;
    for (i=0;i<32;i++){
        fprintf(traza," %3d ", program->registers[i]);
    }
}
void fprintTitle(FILE* traza, Program* program){
    fprintf(traza," PC FASE");
    fprintf(traza," %s",program->nameRegisters[0]);
    fprintf(traza," %s",program->nameRegisters[1]);
    int i;
    for (i=2;i<32;i++){
        fprintf(traza,"  %s",program->nameRegisters[i]);
    }
    fprintf(traza,"\n");
}
void fprintLinesControl(FILE* linesControl, Program* program){
	fprintf(linesControl,"RegDst:  %c\n",program->linesControl[0]);
    fprintf(linesControl,"Jump:    %c\n",program->linesControl[1]);
    fprintf(linesControl,"Branch:  %c\n",program->linesControl[2]);
    fprintf(linesControl,"MemRead: %c\n",program->linesControl[3]);
    fprintf(linesControl,"MemToReg:%c\n",program->linesControl[4]);
    fprintf(linesControl,"ALUOP1:  %c\n",program->linesControl[5]);
    fprintf(linesControl,"ALUOP2:  %c\n",program->linesControl[6]);
    fprintf(linesControl,"MemWrite:%c\n",program->linesControl[7]);
    fprintf(linesControl,"ALUSrc:  %c\n",program->linesControl[8]);
    fprintf(linesControl,"RegWrite:%c\n",program->linesControl[9]);
}
void setLinesControl(Instruction in,Program* program){
     if (
		!strcmp(in.function,"add") ||
		!strcmp(in.function,"sub") ||
		!strcmp(in.function,"mul") ||
		!strcmp(in.function,"div")
		){
		    program->linesControl[0]='1';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='0';
		    program->linesControl[4]='0';
		    program->linesControl[5]='1';
		    program->linesControl[6]='0';
		    program->linesControl[7]='0';
		    program->linesControl[8]='0';
		    program->linesControl[9]='1';
    }
    else if(
        !strcmp(in.function,"addi") ||
        !strcmp(in.function,"subi")){
            program->linesControl[0]='0';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='0';
		    program->linesControl[4]='0';
		    program->linesControl[5]='0';
		    program->linesControl[6]='0';
		    program->linesControl[7]='0';
		    program->linesControl[8]='1';
		    program->linesControl[9]='1';

    }
    else if(
        !strcmp(in.function,"beq") ||
        !strcmp(in.function,"blt") ||
        !strcmp(in.function,"bgt")){
            program->linesControl[0]='x';
		    program->linesControl[1]='0';
		    program->linesControl[2]='1';
		    program->linesControl[3]='0';
		    program->linesControl[4]='x';
		    program->linesControl[5]='0';
		    program->linesControl[6]='1';
		    program->linesControl[7]='0';
		    program->linesControl[8]='0';
		    program->linesControl[9]='0';

    }
    else if (
		!strcmp(in.function,"j") ||
		!strcmp(in.function,"jal") ||
		!strcmp(in.function,"jr")
		){
		    program->linesControl[0]='x';
		    program->linesControl[1]='1';
		    program->linesControl[2]='x';
		    program->linesControl[3]='0';
		    program->linesControl[4]='x';
		    program->linesControl[5]='x';
		    program->linesControl[6]='x';
		    program->linesControl[7]='0';
		    program->linesControl[8]='x';
		    program->linesControl[9]='0';

    }
    else if (
		!strcmp(in.function,"lw") ||
		!strcmp(in.function,"la")
		){
		    program->linesControl[0]='0';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='1';
		    program->linesControl[4]='1';
		    program->linesControl[5]='0';
		    program->linesControl[6]='0';
		    program->linesControl[7]='0';
		    program->linesControl[8]='1';
		    program->linesControl[9]='1';

    }
    else if (
		!strcmp(in.function,"sw")
		){
		    program->linesControl[0]='x';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='0';
		    program->linesControl[4]='x';
		    program->linesControl[5]='0';
		    program->linesControl[6]='0';
		    program->linesControl[7]='1';
		    program->linesControl[8]='1';
		    program->linesControl[9]='0';

    }
}

void printRegisters(Program* program){
    int i;
    for (i=0;i<32;i++){
        printf(" %3d ", program->registers[i]);
    }
}

void exProgram(Program* program){
    FILE* linesControl = fopen("Lines Control.txt","w");
    FILE* traza = fopen("Traza.txt","w");


    for (program->PC=0;program->PC<=program->counterInstruction;program->PC++){
        //showInstruction(program->instructions[program->PC]);
        if(!strcmp(program->instructions[program->PC].function,"add")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

            add(program->instructions[program->PC],program,linesControl,traza);
        }
        else if(!strcmp(program->instructions[program->PC].function,"sub")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

            sub(program->instructions[program->PC],program,linesControl,traza);
        }
        else if(!strcmp(program->instructions[program->PC].function,"addi")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

            addi(program->instructions[program->PC],program,linesControl,traza);
        }
        else if(!strcmp(program->instructions[program->PC].function,"subi")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

            subi(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"mul")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

            mul(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"div")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

            div_m(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"beq")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		beq(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"blt")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		blt(program->instructions[program->PC],program,linesControl,traza);
       		//printf("hola\n");

        }
        else if(!strcmp(program->instructions[program->PC].function,"bgt")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		bgt(program->instructions[program->PC],program,linesControl,traza);

        }

        else if(!strcmp(program->instructions[program->PC].function,"lw")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		lw(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"sw")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		sw(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"la")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		la(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"j")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		jump(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"jal")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		jal(program->instructions[program->PC],program,linesControl,traza);

        }
        else if(!strcmp(program->instructions[program->PC].function,"jr")){
        	//Lineas de control
        	fprintInstruction(linesControl,program->instructions[program->PC]);
        	setLinesControl(program->instructions[program->PC],program);
        	fprintLinesControl(linesControl,program);
        	fprintf(linesControl,"\n");
       	 	showInstruction(program->instructions[program->PC]);

       		jr(program->instructions[program->PC],program,linesControl,traza);

        }

    }
    fclose(linesControl);
    fclose(traza);
}
int getPClabel(char* label,Program* program){
    int i;
    for (i=0;i<program->counterLabel;i++){
        //printf("%s-%s\n",program->labels[i].name,label);
        if (! strcmp(program->labels[i].name, label)){
        	return program->labels[i].PC;
        }
    }
    return -1;
}
void showLabels(Program* program){
    int i;
    for (i=0;i<program->counterLabel;i++){
        printf("%s %d\n",program->labels[i].name,program->labels[i].PC);

    }
}























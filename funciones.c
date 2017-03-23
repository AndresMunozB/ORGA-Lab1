#include "estructuras.h" //esto ver si se puede sacar ya que esta incluido en funcinoes.h
#include "funciones.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define CANTIDAD 100000
#define LI 50


int existsFile(char* filename) {
	FILE* f = NULL;
	f = fopen(filename,"r");
	if (f == NULL) 
		return 0;
	else {
		fclose(f);
		return 1;
	}
	return 0;
}

/*
 * Funcion rtrim
*/
void rtrim(char* string){
	while(string[strlen(string)-1]==' ' 
		|| string[strlen(string)-1]=='\n' 
		|| string[strlen(string)-1]=='\t'
		|| string[strlen(string)-1]=='\r'){
		string[strlen(string)-1]='\0';
	}
}

Program* programInit(char *filename){
	//Pidiendo memoria
	Program *program= (Program*) malloc(sizeof(Program));

	//Inicializando program counter
	program->PC=0;


	//Agregando los nameRegisters
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

	//Reseteando los regitros
	int i;
	for (i=0;i<32;i++){
		program->registers[i]=0;
		//printf("%s\n", program->nameRegisters[i]);
	}

	//Adding instructions
	FILE* file;
	file = fopen(filename,"r");
	char buffer[LI];
	int counter=0;
	while (!feof(file)){
		memset(buffer,0,LI);
		fgets(buffer,LI,file);
		rtrim(buffer);
		strcpy(program->instructions[counter], buffer);
		counter+=1;
	}
	program->quantityInstructions = counter;
	fclose(file);
	return program;
}

void showProgram(Program *program){
	int i;
	printf("NUMERO DE INSTRUCCIONES: %d\n",program->quantityInstructions );
	printf("CODIGO:\n");
	for (i=0;i<program->quantityInstructions;i++){
		printf("%s\n",program->instructions[i] );
	}
	printf("REGISTROS:\n");
	for (i=0;i<32;i++){
		printf("%s: %d\n",program->nameRegisters[i],program->registers[i] );
	}
}
/*esta funcion no creo que la utilice! se supone que con el nombre de la instruccion se saben los argumentos
int quantityArgs(char instruction[]){
	int i;
	int counter=0;
	for (i=0;i<strlen(instruction);i++){
		if (instruction[i]==' '){
			counter++;
		}
	}
	if (counter == 3){
		return 3;
	}
	else if(counter == 2){
		2
	}
	else{
		return 0;
	}
}*/
void exInstruction(char instruction[], Program *program){
	/*hacer un if con todas las fucniones que contengan 3 argumentos, luego sacar esos 3 argumentos y llamar a la funciones correpondiente
	del mismo modo se hacen con las funcinoes que tienen 2 y 1 argumentos...
	deberian ser como 2 o 3 if y ahi se derivan a las siguiente funciones dependiendo de la instruccion.
	leer lo de arriba (funcion comentada anterior)
	*/
	//hay que preguntar que instruccion es...
	char funtion[30];
	char arg1[30];
	char arg2[30];
	char arg3[30];
	memset(funtion,0,30);
	memset(arg1,0,30);
	memset(arg2,0,30);
	memset(arg3,0,30);
	/*obteniendo los string correspondintes*/
	int i=0;
	while (instruction[i] != ' '){
		funtion[i] = instruction[i];
		i++;
	}
	//printf("%s\n", funtion);
	if (
		!strcmp(funtion,"add") ||
		!strcmp(funtion,"addi") ||
		!strcmp(funtion,"sub") ||
		!strcmp(funtion,"subi") ||
		!strcmp(funtion,"mul") ||
		!strcmp(funtion,"div") ||
		!strcmp(funtion,"beq") ||
		!strcmp(funtion,"blt") ||
		!strcmp(funtion,"bgt") 
		){
		printf("%s: es igual\n", funtion );
	}
	
}
/*void exProgram(Program *program){
	int i;
	for (program->PC=0;program->PC<program->quantityInstructions;program->PC++){
		if(strlen(program->instructions[program->PC])!=0){
			printf("%s -- %d\n",program->instructions[program->PC] ,isInstrution(program->instructions[program->PC]));
		}
	}
}*/


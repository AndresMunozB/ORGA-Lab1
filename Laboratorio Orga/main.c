#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"



int main(){
    //printf("hola\n");
    Program* program = (Program*)programInit("iterativo.asm");
    int index = getIndexRegister("$s7",program);
    printf("index: %d",index);
    //printf("%d",program->PC);
    //printf("hola\n");
    //showInstruction(program->instructions[0]);
    return 0;

}

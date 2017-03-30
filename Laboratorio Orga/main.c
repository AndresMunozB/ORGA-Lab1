#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"



int main(){

    Program* program = (Program*)programInit("recursivo.asm");
    exProgram(program);

    return 0;

}

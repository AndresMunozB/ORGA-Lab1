#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"



int main(){

    Program* program;
	char nameFileEntrada[250];
	char nameFileLC[250];
	char nameFileT[250];
	char option[250];


    do{
		printf("         MENU\n");
		printf("1) Ejecutar programa.\n");
		printf("2) Salir\n" );
		printf("\nIngrese una option: ");
		memset(option,0,sizeof(option));
		fflush(stdin);
		scanf("%s",option);
		if (!strcmp(option,"1")){

            memset(nameFileEntrada,0,sizeof(nameFileEntrada));
            printf("Ingrese el nombre del archivo de entrada: ");
            fflush(stdin);
            scanf("%s", nameFileEntrada);

            memset(nameFileLC,0,sizeof(nameFileLC));
            printf("Ingrese el nombre del archivo de salida para lineas de control: ");
            fflush(stdin);
            scanf("%s", nameFileLC);

            memset(nameFileT,0,sizeof(nameFileT));
            printf("Ingrese el nombre del archivo de salida para la traza: ");
            fflush(stdin);
            scanf("%s", nameFileT);

            if (existsFile(nameFileEntrada) && strcmp(nameFileLC,nameFileT)){
                program = (Program*) programInit(nameFileEntrada);
                exProgram(program,nameFileLC,nameFileT);
            }
            else if(!strcmp(nameFileLC,nameFileT)){
                printf("No se realizo ninguna accion debido a que\nlos nombres de los archivos de salida son iguales\n");
            }

            else{
                    printf("El archivo de entrada no existe\n\n");
            }

		}

		}while(strcmp(option,"2"));

    return 0;

}

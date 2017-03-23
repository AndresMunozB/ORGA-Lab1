#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H
/*
 * Funtion existFile
 * funcion que verifica si un archivo de texto plano existe
 * @param char* filename, nombre del archivo
 * @return entero 1 en caso de que si exista y 0 en caso contrario
*/
int 	existsFile 				(char* filename);

/*
 * Funtion rtrim
 * funcion que elimina todos los caracteres de espacio (" ") al final de un string
 * @param char* string, string a modificar
*/
void rtrim (char* string);
/*
 * Funtion programInit
 * Funcion que inicializa una estructura 
 *
*/
Program* programInit(char *filename);
void showProgram(Program *program);
void exInstruction(char instruction[], Program *program);
//int isInstrution(char intruction[]); //cambie el nombre de esto y aparte comente la funcion..


#endif
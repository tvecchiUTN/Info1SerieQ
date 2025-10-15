#ifndef __GENEAN13_H
#define __GENEAN13_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define NDIGIT 13 //COntando el salto de linea

#define OK 1
#define ERR_NO_CRT -1
#define ERR_NO_RD -2
#define ERR_NO_WT -3
#define ERR_NO_CLSE -4

int genFileEAN(const char* name, int nLines);

int fileDF(const char *name, int nLines);

int checkDF(const char *name);

void llenarVec(char *vec, int n);

void addDF(char *linea);

//Calcular cual es el digito verificador
//Para luego devolverlo
int calcDF(const int* linea);

#endif
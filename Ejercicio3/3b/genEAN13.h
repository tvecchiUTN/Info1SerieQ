#ifndef __GENEAN13_H
#define __GENEAN13_H

#include <unistd.h>
#include <fcntl.h>

#define OK 1
#define ERR_NO_CRT -1
#define ERR_NO_RD -2
#define ERR_NO_WT -3
#define ERR_NO_CLSE -4

int genFileEAN(const char* name, int nLines);

int fileDF(const char *name, int nLines);

void llenarVec(char *vec, int n);

void addDF(char *linea);

#endif
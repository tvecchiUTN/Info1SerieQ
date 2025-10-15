#ifndef __INVFILE_H
#define __INVFILE_H

#include <fcntl.h>
#include <unistd.h>

int invertirArchivo(const char *fileIn, const char *fileOut);

void invertirBuff(char* s, size_t sz);

#endif
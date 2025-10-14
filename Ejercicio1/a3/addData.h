#ifndef __ADDDATA_H
#define __ADDDATA_H

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int agregarInicio(const char *nombre, const void *data, int size);

int checkParam(const char *nombre, const void *data, int size);

#endif
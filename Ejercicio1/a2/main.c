#include <stdio.h>
#include <string.h>
#include "addData.h"

int main()
{
    char *name = "prueba.txt";
    char *info = "Si todo salio bien, esto debe estar antes de lo escrito antes---";
    int sz = strlen(info);

    agregarInicio(name, info, sz);

    return 1;
}
#include <stdio.h>
#include <string.h>
#include "addData.h"

int main()
{
    char *name = "prueba.txt";
    char *info = "INICIO DE TEXTO: ";
    int sz = strlen(info);

    agregarInicio(name, info, sz);

    return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "genEAN13.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Faltan arguementos\n");
        return 1;
    }

    char *name = NULL;
    int cdadLineas = 0;
    for (int i = 0; i < argc; i++)
    {
        if (i == 1)
        {
            cdadLineas = atoi(argv[1]);
            if (cdadLineas < 0)
            {
                fprintf(stderr, "Cantidad negativa, solo numeros positivos\n");
                return 1;
            }
        }

        else if (i == 2)
        {
            name = argv[2];
        }
    }
    
    printf("%d\n", checkDF("List-ean03.txt"));
}
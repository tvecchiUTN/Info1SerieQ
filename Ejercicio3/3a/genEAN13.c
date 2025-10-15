#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include "genEAN13.h"

#define NDIGIT 12

int genFileEAN(const char* name, int nLines)
{
    int code = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (code < 0)
    {
        fprintf(stderr, "Error creando el archivo\n");
        return ERR_NO_CRT;
    }

    char buffWrite[NDIGIT+1];

    for (int i = 0; i < nLines; i++)
    {
        llenarVec(buffWrite, NDIGIT+1);

        if(write(code, buffWrite, NDIGIT+1) < 0)
        {
            fprintf(stderr, "Error escribiendo en el archivo\n");
            return ERR_NO_WT;
        }
    }

    if(close(code) < 0)
    {
        return ERR_NO_CLSE;
    }

    return OK;
}

void llenarVec(char *vec, int n)
{
    static int flagRand = 1;
    if(flagRand)
    {
        srand(time(NULL));
        flagRand = 0;
    }

    for(int i = 0; i < n-1; i++)
    {
        if(!i)
        {
            *vec = (rand() % 9) + '1';    
            continue;
        }
        *(vec + i) = (rand() % 10) + '0';
    }

    *(vec + n-1) = '\n';
}
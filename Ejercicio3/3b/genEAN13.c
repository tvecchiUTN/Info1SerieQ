#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include "genEAN13.h"

#define NDIGIT 13

int genFileEAN(const char *name, int nLines)
{
    int code = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (code < 0)
    {
        fprintf(stderr, "Error creando el archivo\n");
        return ERR_NO_CRT;
    }

    char buffWrite[NDIGIT];

    for (int i = 0; i < nLines; i++)
    {
        llenarVec(buffWrite, NDIGIT);

        if (write(code, buffWrite, NDIGIT) < 0)
        {
            fprintf(stderr, "Error escribiendo en el archivo\n");
            return ERR_NO_WT;
        }
    }

    if (close(code) < 0)
    {
        return ERR_NO_CLSE;
    }

    return OK;
}

int fileDF(const char *name, int nLines)
{
    int file = open(name, O_RDONLY);
    if (file < 0)
    {
        fprintf(stderr, "Error abriendo el archivo\n");
        return ERR_NO_CRT;
    }

    int fileDF = open("fileDF.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fileDF < 0)
    {
        fprintf(stderr, "Error creando el archivo\n");
        return ERR_NO_CRT;
    }

    char buffRead[NDIGIT + 1];

    for (int i = 0; i < nLines; i++)
    {
        if (read(file, buffRead, NDIGIT) < 0)
        {
            fprintf(stderr, "Error leyendo el archivo\n");
            return ERR_NO_RD;
        }

        addDF(buffRead);
        buffRead[NDIGIT] = '\n';

        if (write(fileDF, buffRead, NDIGIT+1) < 0)
        {
            fprintf(stderr, "Error escribiendo en el archivo\n");
            return ERR_NO_WT;
        }
    }

    close(file);
    close(fileDF);

    return OK;
}

void llenarVec(char *vec, int n)
{
    static int flagRand = 1;
    if (flagRand)
    {
        srand(time(NULL));
        flagRand = 0;
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (!i)
        {
            *vec = (rand() % 9) + '1';
            continue;
        }
        *(vec + i) = (rand() % 10) + '0';
    }

    *(vec + n - 1) = '\n';
}

void addDF(char *linea)
{
    int auxInteger[NDIGIT-1];

    for (int i = 0; i < NDIGIT-1; i++)
    {
        auxInteger[i] = linea[i] - '0';
    }

    int sumaP = 0;
    int sumaImp = 0;

    int decSup = 0;
    for (int i = 0; i < NDIGIT-1; i++)
    {
        if (!(i % 2))
        {
            sumaP += auxInteger[i];
        }
        else
        {
            sumaImp += auxInteger[i];
        }
    }

    sumaImp *= 3;

    sumaP += sumaImp;

    decSup = sumaP;
    for (int i = 0; i < 10; i++)
    {
        decSup++;
        if (!(decSup % 10))
        {
            break;
        }
    }

    int df = decSup - sumaP;

    linea[NDIGIT - 1] = df + '0';
}
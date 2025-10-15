#include <stdio.h>

#include "genEAN13.h"

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

    for (int i = 0; i < nLines; i++)
    {
        char buffRead[NDIGIT + 1];

        if (read(file, buffRead, NDIGIT) < 0)
        {
            fprintf(stderr, "Error leyendo el archivo\n");
            return ERR_NO_RD;
        }

        addDF(buffRead);
        buffRead[NDIGIT] = '\n';

        if (write(fileDF, buffRead, NDIGIT + 1) < 0)
        {
            fprintf(stderr, "Error escribiendo en el archivo\n");
            return ERR_NO_WT;
        }
    }

    close(file);
    close(fileDF);

    return OK;
}

#define N 16
int checkDF(const char *name)
{
    int f = open(name, O_RDONLY);
    if (f < 0)
    {
        fprintf(stderr, "Error abriendo el archivo\n");
        return ERR_NO_CRT;
    }

    int nLinea = 1;
    while (1)
    {
        char buffRead[N];

        int leido = read(f, buffRead, NDIGIT+1);
        if (leido < 0)
        {
            fprintf(stderr, "Error leyendo el archivo\n");
            return ERR_NO_RD;
        }
        if(leido < NDIGIT + 1)
        {
            break;
        }
        int auxNums[NDIGIT];
        int i;
        for(i = 0; buffRead[i] != '\n'; i++)
        {
            if(!((buffRead[i] >= '0') && (buffRead[i] <= '9')))
            {
                printf("La linea %d posee error por tipo de digitos\n", nLinea);
                nLinea++;
                continue;
            }
            auxNums[i] = buffRead[i] - '0';
        }
        if(i != 13)
        {
            printf("La linea %d posee error por cantidad de digitos\n", nLinea);
            nLinea++;
            continue;
        }

        int df = calcDF(auxNums);

        if(df != auxNums[NDIGIT-1])
        {
            printf("La linea %d posee error por digito verificador\n", nLinea);
        }
        nLinea++;
    }

    if(close(f) < 0)
    {
        fprintf(stderr, "Error cerrando el archivo\n");
        return ERR_NO_CLSE;
    }

    return OK;
}
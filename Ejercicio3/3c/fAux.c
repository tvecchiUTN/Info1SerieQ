#include "genEAN13.h"

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

    int df = calcDF(auxInteger);

    linea[NDIGIT - 1] = df + '0';
}

int calcDF(const int* linea)
{
    int sumaP = 0;
    int sumaImp = 0;

    int decSup = 0;
    for (int i = 0; i < NDIGIT-1; i++)
    {
        if (!(i % 2))
        {
            sumaP += linea[i];
        }
        else
        {
            sumaImp += linea[i];
        }
    }

    sumaImp *= 3;

    sumaP += sumaImp;

    decSup = sumaP;
    for (int i = 0; i < 10; i++)
    {
        if (!(decSup % 10))
        {
            break;
        }

        decSup++;
    }

    int df = decSup - sumaP;

    return df;
}
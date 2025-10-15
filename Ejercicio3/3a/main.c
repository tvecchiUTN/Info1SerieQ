#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define NDIGIT 12

void llenarVec(char *vec, int n);

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

    int code = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (code < 0)
    {
        fprintf(stderr, "Error creando el archivo\n");
        return 1;
    }

    char buffWrite[NDIGIT+1];
    for (int i = 0; i < cdadLineas; i++)
    {
        llenarVec(buffWrite, NDIGIT+1);

        if(write(code, buffWrite, NDIGIT+1) < 0)
        {
            fprintf(stderr, "Error escribiendo en el archivo\n");
        }
    }
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
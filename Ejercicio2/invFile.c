#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invFile.h"

#define ERR_NO_EX_OPEN -1
#define ERR_EXIST_DEST -2
#define ERR_NO_CREATE_DEST -3
#define ERR_RD_ORIGIN -4
#define ERR_WT_CLOSE_DEST -5
#define ERR_OTHER -6
#define OK 1

#define N 1024

int invertirArchivo(const char *fileIn, const char *fileOut)
{
    int origen, destino;

    origen = open(fileIn, O_RDONLY);
    if(origen < 0){return ERR_NO_EX_OPEN;}

    destino = open(fileOut, O_WRONLY | O_CREAT | O_EXCL, 0664);
    if(destino < 0)
    {
        return ERR_EXIST_DEST;
    }

    size_t leido = 0;

    size_t recorridoInicial = lseek(origen, 0, SEEK_END);
    size_t restantes = recorridoInicial;
    while(restantes > 0)
    {
        size_t szRead = (restantes < N) ? restantes : N;
        char buffRead[N];

        lseek(origen, restantes - szRead, SEEK_SET);

        leido = read(origen, buffRead, szRead);

        if(leido < 0){return ERR_RD_ORIGIN;}

        invertirBuff(buffRead, leido);

        if(write(destino, buffRead, leido) < 0){return ERR_WT_CLOSE_DEST;}
        
        restantes -= leido;
    }

    if(close(origen) < 0){return ERR_WT_CLOSE_DEST;}
    if(close(destino) < 0){return ERR_WT_CLOSE_DEST;}

    return OK;
}

void invertirBuff(char* s, size_t sz)
{
    int i, j;
    char temp;
    for(i = 0, j = sz-1; i < j; i++, j--)
    {
        temp = *(s + i);
        *(s + i) = *(s +j);
        *(s + j) = temp;
    }
}
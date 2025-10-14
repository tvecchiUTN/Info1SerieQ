#include <stdio.h>
#include <errno.h>
#include "addData.h"

#define N 1024

#define ERR_AL_CRE -4
#define ERR_AL_WT -3
#define ERR_AL_MOD -2
#define ERR_AL_UNKOWN -1

int agregarInicio(const char *nombre, const void *data, int size)
{
    if(!checkParam(nombre, data, size))
    {
        return ERR_AL_UNKOWN;
    }

    int fd = open(nombre, O_RDWR);
    if(fd < 0)
    {
        if(errno == EACCES) //nO tengo los permisos
        {
            return ERR_AL_MOD;
        }
        else if(errno == ENOENT) //No existe
        {
            fd = open(nombre, O_RDWR | O_CREAT, 0664);
            if(fd < 0)
            {
                return ERR_AL_CRE;
            }
        }
        else
        {
            return ERR_AL_UNKOWN;
        }
    }
    
    char auxBuf[N];
    size_t auxRead = 0;
    size_t auxWrite = 0;

    auxRead = read(fd, auxBuf, N);

    lseek(fd, 0, SEEK_SET);

    auxWrite = write(fd, data, size);

    if(auxWrite < 0)
    {
        return ERR_AL_WT;
    }
    
    if(write(fd, auxBuf, auxRead))
    {
        return ERR_AL_WT;
    }
    
    if(close(fd) < 0)
    {
        return ERR_AL_WT;
    }

    return auxWrite;
}

#define OK 1
#define ERROR 0

int checkParam(const char *nombre, const void *data, int size)
{ 
    if(!nombre){fprintf(stderr, "Error de parametros: parametro nombre es NULL\n"); return ERROR;}

    if(!data){fprintf(stderr, "Error de parametros: parametro data es NULL\n"); return ERROR;}

    if(!size){fprintf(stderr, "Error de parametros: parametro size es 0\n"); return ERROR;}

    return OK;
}
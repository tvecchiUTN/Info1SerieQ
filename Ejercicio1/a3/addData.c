#include <stdio.h>
#include <errno.h>
#include "addData.h"

#define ERR_AL_CRE -4
#define ERR_AL_WT -3
#define ERR_AL_MOD -2
#define ERR_AL_UNKOWN -1

#define MINLECTURA 1024

#define TEMPORAL "temporal.txt"

int agregarInicio(const char *nombre, const void *data, int size)
{
    if(!checkParam(nombre, data, size))
    {
        return ERR_AL_UNKOWN;
    }

    int original = open(nombre, O_RDONLY);
    if(original < 0)
    {
        if(errno == EACCES) //No tengo los permisos
        {
            return ERR_AL_MOD;
        }
        else if(errno == ENOENT) //No existe
        {
            original = open(nombre, O_RDWR | O_CREAT, 0664);
            if(original < 0)
            {
                return ERR_AL_CRE;
            }
        }
        else
        {
            return ERR_AL_UNKOWN;
        }
    }
    
    int temp = open(TEMPORAL, O_WRONLY | O_CREAT, 0664);
    if(temp < 0){printf("Error creando archivo temporal\n"); return ERR_AL_CRE;}

    size_t escrito = 0;

    write(temp, data, size); //Verifico error

    int auxEscrito = 0;
    while(1)
    {
        char buffRead[MINLECTURA];
        auxEscrito = read(original, buffRead, MINLECTURA);
        if(auxEscrito < MINLECTURA) //Verificar si es mejor EOR
        {
            escrito += write(temp, buffRead, auxEscrito); //Verificar escritura
            break;
        }

        escrito += write(temp, buffRead, MINLECTURA); //Verificar escritura
    }

    if(close(temp) < 0){return ERR_AL_WT;}
    if(close(original) < 0){return ERR_AL_WT;}

    remove(nombre);

    rename(TEMPORAL, nombre);

    return escrito;
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
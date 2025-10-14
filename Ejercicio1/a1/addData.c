#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define N 1024

int agregarInicio(const char *nombre, const void *data, int size)
{
    int fd = open(nombre, O_RDWR);
    if(fd < 0){fprintf(stderr, "Error al abrir archivo\n"); return -1;}
    
    char auxBuf[N];
    size_t auxRead = 0;
    size_t auxWrite = 0;

    auxRead = read(fd, auxBuf, N);

    lseek(fd, 0, SEEK_SET);

    auxWrite = write(fd, data, size);

    write(fd, auxBuf, auxRead);

    close(fd);

    return auxWrite;
}
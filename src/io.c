#include "include/io.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


char* read_file(const char* filename)
{
    char * buffer = 0;
    long length;
    FILE * f = fopen (filename, "rb");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = calloc (length, length);

        if (buffer)
            fread (buffer, 1, length, f);

        fclose (f);
    }

    return buffer;
}

unsigned int file_exists(const char* filename)
{
    if(access(filename, F_OK) != -1)
        return 1;

    return 0;
}

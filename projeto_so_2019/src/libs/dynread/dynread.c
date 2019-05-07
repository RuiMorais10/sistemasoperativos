#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "dynread.h"

#define READSIZE 256

char *strdup(const char *string) {
    char *dup = calloc(1, strlen(string) + 1);  // allocate & empty buffer
    if(!dup) {
        errno = ENOMEM;
        return NULL;
    }
    else memcpy(dup, string, strlen(string));
    return dup;
}

char* readLine(int* size) {
    char ch;
    char* buffer;

    size_t read_total = 0, buffsize = 256;
    ssize_t read_quant = 0;

    buffer = malloc(buffsize * sizeof(char));
    if(!buffer) {
        errno = ENOMEM;
        *size = 0;
        return NULL;
    }

    while(1) {
        read_quant = read(STDIN_FILENO, &ch, 1);

        if(read_quant == -1) {          // error reading
            errno = EINTR;              // error reading
            return NULL;
        } else if(read_quant == 0) {    // EOF
            if(read_total == 0) {
                free(buffer);
                *size = 0;
                return NULL;
            }
            break;
        } else {
            if(buffsize == read_total) {    // realloc to new size
                buffsize = buffsize * 2;
                buffer = realloc(buffer, buffsize);
            }
            buffer[read_total] = ch;
            if(ch == '\n') {
                if(read_total == 0) {
                    free(buffer);
                    *size = 0;
                    return NULL;
                } else {
                    break;
                }
            }
            
            read_total++;
        }
    }


    buffer[strlen(buffer) - 1] = '\0';
    *size = strlen(buffer) - 1;

    return buffer;
}

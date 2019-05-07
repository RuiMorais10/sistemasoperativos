#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "readline.h"

char* readline(int* size) {
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

        if(read_quant == 0) {               // EOF
            if(read_total == 0) {
                free(buffer);
                *size = 0;
                return NULL;
            }
            break;
        } else {                            // sometimes was read or an error was emmited
            if(read_quant == -1) {          // error reading
                errno = EINTR;
                return NULL;
            }

            if(buffsize == read_total) {    // realloc to new size
                buffsize = buffsize + (buffsize / 2);
                buffer = realloc(buffer, buffsize);
            }
            buffer[read_total] = ch;
            if(ch == '\n' || ch == '\r') {
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

    buffer[read_total] = '\0';
    *size = strlen(buffer) - 1;

    return buffer;
}

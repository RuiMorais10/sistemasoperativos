#include <errno.h>
#include <stdlib.h>

#include "strdup.h"

char *strdup(const char *string) {
    char *dup = calloc(1, strlen(string) + 1);  // allocate & empty buffer
    if(!dup) {
        errno = ENOMEM;                         // *alloc should do this by default, just in case
        return NULL; 
    }
    else memcpy(dup, string, strlen(string));
    return dup;
}

#ifndef DYNREAD_H
#define DYNREAD_H

/**
 * @brief Reads input from stdin and returns it as a '\0' ended char array.
 * 
 * @param size   Pointer to an int where the size of the array will be passed. Size will be the position of '\0'
 * @return char* Buffer allocated to hold the input from stdin.
 */
char* readline(int* size);

#endif
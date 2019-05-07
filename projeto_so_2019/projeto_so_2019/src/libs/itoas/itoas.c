#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief divides a number by 10 to return the ammount of digits necessary to represent it
 * 
 * @param   number  
 * @return  int     ammount of digits necessary to represent the number in a string
 */
int pseudolog(int number);

// Only works with int
int itoas(char* string, int number) {
	int division = 0,       //  
		modulus = 0;        //  
	size_t length = 0;      //  
    bool negative;          //  signal flag

    if(!string)             // string points to NULL, impossible to continue
        return 0;

    if(number == 0) {       // number == 0 => easy
        string[0] = '0';
        string[1] = 0;
        return 1;
    }

    if(number < 0) {        //  number < 0 => flip it
        length += 1;        //  add 1 extra space for '-'
        negative = true;
        number = -number;
    }

    length += pseudolog(number);

    if(negative) {
        string[0] = '-';
        for(;division < length - 1; division++) {
            modulus = number % 10;
            number = number / 10;
            string[length - (division+1)] = modulus + '0';
        }
    } else {
        for(;division < length; division++) {
            modulus = number % 10;
            number = number / 10;
            string[length - (division+1)] = modulus + '0';
        }
    }

    string[length] = '\0';
    return length;
}

int pseudolog(int number) {
    int size = 0;
    while(number) { number /= 10; size++; }
    return size;
}
/*
 * gcc day4.c libs/md5.c
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "libs/md5.h"

#define NUMBER_OF_ZEROS 6    // for 1st or 2nd part of task

int main()
{
    int counter = 0;
    bool found = false;
    do
    {
        char key[1000] = "ckczppom";     // secret key
        char digits[100];
        sprintf(digits, "%d", counter);
        strcat(key, digits);             // prepare input
        
        uint8_t result[16];
        md5String(key, result);          // calculate MD5

        char zeros[7] = "";
        for (int i = 0; i < 3; ++i)
        {
            char chunk[3];
            sprintf(chunk, "%02x", result[i]);
            strcat(zeros, chunk);        // select first 6 characters
        }
 
        found = true;                    // check, if all zeros
        for (int i = 0; i < NUMBER_OF_ZEROS; ++i)
            if (zeros[i] != '0')
            {
                found = false;
                counter++;
                break;
            }
    } while (!found);

    printf("Lowest number is %d\n", counter);
}

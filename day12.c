#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_FILE "day12.txt"

int simple_pass(char* text, int len)
{
    int sum = 0;

    for (int i = 0; i < len; ++i)
        if (isdigit(text[i]) || text[i] == '-')
        {
            char digit[5];
            strncpy(digit, text + i , 4);
            int val = atoi(digit);
            sum += val;
            if (val < 0)
            {
                i++;
                val *= -1;
            }
            if (val > 10) i++;
            if (val > 100) i++;
            if (val > 1000) i++;
        }
    return sum;
}

int parse_json(char* text, int ignore)
{
    static int i = 0;
    int sum = 0;

    for(; i < strlen(text); ++i)
    {
        if (isdigit(text[i]) || text[i] == '-')
        {
            char digit[5];
            strncpy(digit, text + i , 4);
            int val = atoi(digit);
            sum += val;
            if (val < 0)
            {
                i++;
                val *= -1;
            }
            if (val > 10) i++;
            if (val > 100) i++;
            if (val > 1000) i++;
        }
        else if (text[i] == '}')   // end of object
        {
            if (ignore > 0)
            {
                sum = 0;
                ignore--;
            }
            break; // return sum;
        }
        else if (text[i] == '{')   // recursively analyze next object
        {
            i++;
            sum += parse_json(text, ignore);
        }
        else if (strncmp(text + i, ":\"red\"", 5) == 0)
        {
            ignore++;
            i += 5;    // speed up parsing
        }
    }

    return sum;
}

int main(void)
{
    const char filename[] = INPUT_FILE;
    FILE* input = fopen(filename, "r");
    if (!input)
    {
        fprintf(stderr, "Cant load file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    read = getline(&line, &len, input);

    printf("Sum of all numbers is: %d\n", simple_pass(line, read));
    printf("Sum of numbers without \"red\" is: %d\n", parse_json(line, 0));

    fclose(input);
    free(line);

    return 0;
}

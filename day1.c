#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "day1.txt"

int main()
{
    const char filename[] = INPUT_FILE;
    FILE* input = fopen(filename, "r");
    if (!input)
    {
        fprintf(stderr, "Cant load file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    int level = 0;
    int basement = 0;
    int position = 1;
    while (1)
    {
        char c = fgetc(input);
        if (feof(input)) break;

        if (c == '(') level++;
        else if (c == ')') level--;

        if (basement == 0)
            if (level < 0) basement = position;

        position++; 
    }
    fclose(input);

    printf("Level: %d\n", level);
    printf("First position into basement: %d\n", basement);

    return 0;
}

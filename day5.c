
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INPUT_FILE "day5.txt"

bool has_three_vowels(char* l, size_t len)
{
    char vowels[] = "aeiou";
    int counter = 0;
    for (size_t i = 0; i < len && counter < 3; ++i)
        for (int j = 0; j < 5 && counter < 3; ++j)
            if (l[i] == vowels[j])
                counter++;

    if (counter > 2) return true;
    return false;
}

bool has_double_letter(char* l, size_t len)
{
    for (size_t i = 0; i < len - 1; ++i)
        if (l[i] == l[i + 1]) return true;

    return false;
}

bool has_no_bad_strings(char* l, size_t len)
{
    char bad[] = "abcdpqxy";    
    
    for (size_t i = 0; i < len - 1; ++i)
        for (int j = 0; j < 8; j += 2)
            if (l[i] == bad[j] && l[i + 1] == bad[j + 1]) return false;

    return true;
}

int main()
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

    int nice = 0;

    while ((read = getline(&line, &len, input)) != -1)
    {
        //char test[] = "dvszwmarrgswjxmb";
        //char test[] = "ugknbfddgicrmopn";
        //char test[] = "jchzalrnumimnmhp";
        //char test[] = "ytjwhpaylohorvxd";
        //strcat(line, test); len = strlen(test);
        if (has_three_vowels(line, len)
                && has_double_letter(line, len)
                && has_no_bad_strings(line, len))
        {
            nice++;
            printf("%s", line);
        }
        //break;
    }

    fclose(input);
    free(line);

    printf("Nice strings: %d\n", nice);

    return 0;
}

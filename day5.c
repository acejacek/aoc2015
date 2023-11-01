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

bool has_two_letters_without_overlapping(char* l, size_t len)
{
    for (size_t i = 0; i < len - 3; i++)
        for (size_t j = i + 2; j < len - 1; ++j)
            if (l[i] == l[j] && l[i + 1] == l[j + 1]) return true;

    return false;
}

bool has_letter_that_repeats_with_letter_between(char* l, size_t len)
{
    for (size_t i = 0; i < len - 2; i++)
        if (l[i] == l[i + 2]) return true;

    return false;
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

    int nice_round1 = 0;
    int nice_round2 = 0;

    while ((read = getline(&line, &len, input)) != -1)
    {
        read--;       // cut EOL

        if (has_three_vowels(line, read)
                && has_double_letter(line, read)
                && has_no_bad_strings(line, read))
            nice_round1++;

        if (has_two_letters_without_overlapping(line, read)
                && has_letter_that_repeats_with_letter_between(line, read))
            nice_round2++;
    }

    fclose(input);
    free(line);

    printf("Nice strings for round 1: %d\n", nice_round1);
    printf("Nice strings for round 2: %d\n", nice_round2);

    return 0;
}

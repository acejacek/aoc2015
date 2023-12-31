#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_FILE "day19.txt"

typedef struct
{
    char from[5];
    char to[20];
} Replacement;

void check_alloc (void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
}

unsigned long hash_func(char* string)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *string++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

void shuffle(Replacement* repl, int r)
{
    if (r < 1) return;

    for (int i = 0; i < r - 1; ++i)
    {
        int j = i + rand() / (RAND_MAX / (r - i) + 1);
        Replacement tmp = repl[j];
        repl[j] = repl [i];
        repl[i] = tmp;
    }
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

    Replacement* repl = NULL;
    int replacements;

    for (replacements = 0; (read = getline(&line, &len, input)) > 1; ++replacements)
    {
        repl = realloc(repl, sizeof(Replacement) * (replacements + 1));
        check_alloc(repl);

        sscanf(line, "%s %*s %s",
                repl[replacements].from, repl[replacements].to);
    }

    // read molecule
    read = getline(&line, &len, input);

    if (read < 1)
    {
        fprintf(stderr, "Can't read calibration molecule.\n");
        goto dispose;
    }

    line[--read] = '\0'; // kill EOL;

    unsigned long* new_molecule = NULL;
    int molecule_counter = 0;

    for (int r = 0; r < replacements; ++r) 
    {
        int len = strlen(repl[r].from);
        for (int i = 0; i < read; ++i)
            if (strncmp(repl[r].from, line + i, len) == 0)
            {
                char new_molecule_name[read * 2];  // safe size?
                new_molecule_name[0] = '\0';

                if (i > 0) strncat(new_molecule_name, line, i);
                strcat(new_molecule_name, repl[r].to);
                strcat(new_molecule_name, line + i + len);
                unsigned long hash = hash_func(new_molecule_name);

                int new = 1;
                for (int j = 0; j < molecule_counter; ++j)
                    if (new_molecule[j] == hash)
                        new = 0; break;

                if (new)
                {   
                    new_molecule = realloc(new_molecule, sizeof(unsigned long) * (molecule_counter + 1));
                    check_alloc(new_molecule);
                    new_molecule[molecule_counter++] = hash;
                }

                i += len - 1; // sometimes "from" is longer that 1 char
            } 
    }

    printf("New molecules: %d\n", molecule_counter);
    free(new_molecule);

/* Part 2
 *
 *  based on https://www.reddit.com/r/adventofcode/comments/3xflz8/comment/cy4cu5b/
 *
 * */
    
    srand(time(NULL));

    char target[3000];
    strcpy(target, line);

    int min_replacements = 0;

    while (strcmp(target, "e") != 0)
    {
        char tmp[strlen(target)];
        strcpy(tmp, target);

        for (int r = 0; r < replacements; ++r) 
        {
            int len = strlen(repl[r].to);
            for (int i = 0; i < strlen(target); ++i)
            {
                if (strncmp(repl[r].to, target + i, len) != 0)
                    continue;

                char new_molecule_name[strlen(target)];
                new_molecule_name[0] = '\0';

                if (i > 0) strncat(new_molecule_name, target, i);
                strcat(new_molecule_name, repl[r].from);
                strcat(new_molecule_name, target + i + len);
                
                strcpy(target, new_molecule_name);

                min_replacements++;
            }
        }
        if (strcmp(target, tmp) == 0) // no progress in reduction
        {
            strcpy(target, line);
            min_replacements = 0;
            shuffle(repl, replacements);
        }
    }

    printf("Smallest number of replacements for medicine molecule: %d\n", min_replacements);

dispose:
    fclose(input);
    free(line);
    free(repl);

    return 0;
}

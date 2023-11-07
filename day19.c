#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "day19.text"

typedef struct
{
    char from[5];
    char to[20];
} Replacement;

int replacements = 0;

void check_alloc (void* p)
{
    if (p != NULL) return;

    fprintf (stderr, "Can't allocate memory!\n");
    exit (EXIT_FAILURE);
}

unsigned long hash_func(char* string)
{
    unsigned long hash = 5381;
    int c;

    while (c = *string++)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}
int rec = 0;
void combine(Replacement* repl, Replacement* mix, const int mix_size, const int i)
{   
//    if (++rec > 5) return;
    if (i == mix_size)
    {   
        return;
    }
    while (repl[0].from[0] != '\0')  // breaks at NULL terminator
    {
        mix[i] = repl[0];
        combine(++repl, mix, mix_size, i + 1);
//    if (rec > 5) return;
    }
}
int main (void)
{
    const char filename[] = INPUT_FILE;
    FILE* input = fopen (filename, "r");
    if (!input)
    {
        fprintf (stderr, "Cant load file %s.\n", filename);
        exit (EXIT_FAILURE);
    } 

    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    Replacement* repl = NULL;

    for (replacements = 0; (read = getline (&line, &len, input)) > 1; ++replacements)
    {
        repl = realloc (repl, sizeof(Replacement) * (replacements + 1));
        check_alloc (repl);

        sscanf(line, "%s %*s %s",
                repl[replacements].from, repl[replacements].to);
    }
    repl = realloc (repl, sizeof(Replacement) * (replacements + 1));
    check_alloc (repl);
    repl[replacements].from[0] = '\0';   // add terminator

    // read molecule
    read = getline (&line, &len, input);

    if (read < 1)
    {
        fprintf (stderr, "Can't read callibration molecule.\n");
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
                unsigned long hash = hash_func (new_molecule_name);

                int new = 1;
                for (int j = 0; j < molecule_counter; ++j)
                    if (new_molecule[j] == hash)
                    { 
                        new = 0; break;
                    }

                if (new)
                {   
                    new_molecule = realloc (new_molecule, sizeof(unsigned long) * (molecule_counter + 1));
                    check_alloc (new_molecule);
                    new_molecule[molecule_counter++] = hash;
                }

                i += len - 1; // sometimes "from" is longer that 1 char
            } 
    }
    printf("New molecules: %d\n", molecule_counter);
    free(new_molecule);

    Replacement* mixture = malloc(sizeof(Replacement) * replacements);
    check_alloc(mixture);
    memcpy (mixture, repl, sizeof(Replacement) * replacements);

    combine(repl, mixture, replacements, 0);

    for (int i = 0; i < replacements; ++i)
    {
        printf("%s %s           \t%s %s\n",
                repl[i].from, repl[i].to,
                mixture[i].from, mixture[i].to);
    }

dispose:
    fclose (input);
    free (line);
    free (repl);
    free (mixture);

    return 0;
}

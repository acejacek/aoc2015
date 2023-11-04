#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INPUT_FILE "day13.txt"
#define MY_NAME "aceJacek"

char my_name[] = MY_NAME;

typedef struct Pair
{
    char name[20];
    char target[20];
    int happines;
} Pair;

Pair* pairs = NULL;
int pairs_count = 0;

char** names;
int guests_count = 0;

int max_happines = 0;

void check_alloc(void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
}

int find_index(char* name)
{
    for (int i = 0; i < guests_count; ++i)
        if (strcmp(name, names[i]) == 0)
            return i;

    return -1;
}

void add_name(char* name)
{
    if (find_index(name) >= 0) return;

    guests_count++;
    names = realloc(names, sizeof(char*) * guests_count);
    check_alloc(names);

    char* newname = malloc(sizeof(char) * strlen(name));
    check_alloc(newname);

    strcpy(newname, name);
    names[guests_count - 1] = newname;
}

int check_neighbour(char* name, int i)
{
    if (i == guests_count) i = 0;  // wrap around
    if (i < 0) i = guests_count - 1; // wrap around

    for (int j = 0; j < pairs_count; ++j)
        if (strcmp(pairs[j].name, name) == 0)
            if (strcmp(pairs[j].target, names[i]) == 0)
                return pairs[j].happines;
    return 0;
}

int check_happines(char* name)
{
    int i = find_index(name);

    return check_neighbour(name, i + 1)
        + check_neighbour(name, i - 1);
}

void swap(int a, int b)
{
    char* t;
    t = names[a];
    names[a] = names[b];
    names[b] = t;
}

void permutate(int start, int end)
{
    if (start == end) return;

    for (int i = start; i <= end; ++i)
    {
        int happines = 0;
        for (int j = 0; j < guests_count; ++j)
            happines += check_happines(names[j]);

        if (max_happines < happines) max_happines = happines;

        swap(i, start);
        permutate(start + 1, end);
        swap(i, start);
    }
    return;
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

    while ((read = getline(&line, &len, input)) != -1)
    {
        pairs = realloc(pairs, sizeof(Pair) * (pairs_count + 1));
        check_alloc(pairs);

        char change[5];
        sscanf(line, "%s %*s %s %d %*s %*s %*s %*s %*s %*s %s",
                pairs[pairs_count].name, change,
                &pairs[pairs_count].happines, pairs[pairs_count].target);

        if (change[0] == 'l') pairs[pairs_count].happines *= -1;

        int last = strlen(pairs[pairs_count].target) - 1;
        if (pairs[pairs_count].target[last] == '.') 
            pairs[pairs_count].target[last] = '\0';  // cut the dot

        add_name(pairs[pairs_count].name);
        add_name(pairs[pairs_count].target);  // just in case 

        pairs_count++;
    }

    fclose(input);
    free(line);

    permutate(0, guests_count - 1);
    printf("Happiness: %d\n", max_happines);

    add_name(my_name);
    for (int i = 0; i < guests_count - 1; ++i)
    {
        pairs = realloc(pairs, sizeof(Pair) * (pairs_count + 1));
        check_alloc(pairs);
        strcpy(pairs[pairs_count].name, my_name);
        strcpy(pairs[pairs_count].target, names[i]); 
        pairs[pairs_count].happines = 0;
        pairs_count++;

        pairs = realloc(pairs, sizeof(Pair) * (pairs_count + 1));
        check_alloc(pairs);
        strcpy(pairs[pairs_count].name, names[i]); 
        strcpy(pairs[pairs_count].target, my_name);
        pairs[pairs_count].happines = 0;
        pairs_count++;
    }

    max_happines = 0;
    permutate(0, guests_count - 1);
    printf("Happiness, when %s is at the table: %d\n", my_name,  max_happines);

    for (int i = 0; i < guests_count; ++i)
        free(names[i]);
    free(names);
    free(pairs);

    return 0;
}

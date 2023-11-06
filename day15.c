#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "day15.txt"

typedef enum { RUN, REST } State;

typedef struct
{
    char name[20];
    int capacity;
    int durability;
    int flavour;
    int texture;
    int calories;
} Ingredient;

Ingredient* ingredient;

void check_alloc(void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
}

int mixer(int* mix, const int limit, int pos)
{
    if (pos < 0) return 1;
    mix[pos]++;
    if (mix[pos] > limit)
    {
        mix[pos] = 0;
        if (mixer(mix, limit, pos - 1) == 1) return 1;
    }
    return 0;
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

    int id = 0;

    for (id = 0; (read = getline(&line, &len, input)) != -1; ++id)
    {
        ingredient = realloc(ingredient, sizeof(Ingredient) * (id + 1));
        check_alloc(ingredient);

        char change[5];
        sscanf(line, "%s capacity %d, durability %d, flavor %d, texture %d, calories %d",
                ingredient[id].name, 
                &ingredient[id].capacity,
                &ingredient[id].durability,
                &ingredient[id].flavour,
                &ingredient[id].texture,
                &ingredient[id].calories);
    }

    for (int i = 0; i < id; ++i)
        printf("%s %d, %d, %d, %d, %d\n",
           ingredient[i].name,
           ingredient[i].capacity,
           ingredient[i].durability,
           ingredient[i].flavour,
           ingredient[i].texture,
           ingredient[i].calories);

    const int spoons = 100;
    int best_score = 0;
    for (int i = 0; i < spoons; ++i)
    {
        int capacity = i * ingredient[0].capacity + (spoons - i) * ingredient[1].capacity;
        if (capacity < 0) capacity = 0;

        int durability = i * ingredient[0].durability + (spoons - i) * ingredient[1].durability;
        if (durability < 0) durability = 0;

        int flavour = i * ingredient[0].flavour + (spoons - i) * ingredient[1].flavour;
        if (flavour < 0) flavour = 0;

        int texture = i * ingredient[0].texture + (spoons - i) * ingredient[1].texture;
        if (texture < 0) texture = 0;

        int score = capacity * durability * flavour * texture;
        if (best_score < score) best_score = score;
    }

    int mix[id];
    for (int i = 0; i < id; ++i)
        mix[i] = 0;

    const int sp = 3;

    while (mixer(mix, sp, id - 1) == 0)
    {
        int sum = 0;
        for (int i = 0; i < id; ++i)
        {
            printf("%d ", mix[i]);
            sum += mix[i];
        }
        putchar('\n');
    }

    fclose(input);
    free(line);

    printf("Best score: %d\n", best_score);

    free(ingredient);

    return 0;
}

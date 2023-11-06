#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "day15.txt"

typedef struct
{
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

// iterate array with all possible entries //
int mixer(int* mix, const int limit, int pos)
{
    if (pos < 0) return 0;  // all done

    if (++mix[pos] > limit)
    {
        mix[pos] = 0;
        return  mixer(mix, limit, pos - 1);
    }
    return 1;
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

    int id;

    for (id = 0; (read = getline(&line, &len, input)) != -1; ++id)
    {
        ingredient = realloc(ingredient, sizeof(Ingredient) * (id + 1));
        check_alloc(ingredient);

        sscanf(line, "%*s capacity %d, durability %d, flavor %d, texture %d, calories %d",
                &ingredient[id].capacity,
                &ingredient[id].durability,
                &ingredient[id].flavour,
                &ingredient[id].texture,
                &ingredient[id].calories);
    }

    const int spoons = 100;
    int best_score = 0;
    int best_500_cal = 0;

    int mix[id];
    for (int i = 0; i < id; ++i)
        mix[i] = 0;

    while (mixer(mix, spoons, id - 1))
    {
        int sum = 0;
        for (int i = 0; i < id; ++i)
            sum += mix[i];

        if (sum == spoons)
        {
            int capacity = 0;
            for (int j = 0; j < id; ++j)
                capacity += ingredient[j].capacity * mix[j];
            if (capacity < 0) continue; 

            int durability = 0;
            for (int j = 0; j < id; ++j)
                durability += ingredient[j].durability * mix[j];
            if (durability < 0) continue;

            int flavour = 0;
            for (int j = 0; j < id; ++j)
                flavour += ingredient[j].flavour * mix[j];
            if (flavour < 0) continue;

            int texture = 0;
            for (int j = 0; j < id; ++j)
                texture += ingredient[j].texture * mix[j];
            if (texture < 0) continue;

            int score = capacity * durability * flavour * texture;
            if (best_score < score) best_score = score;
            
            int calories = 0;
            for (int j = 0; j < id; ++j)
                calories += ingredient[j].calories * mix[j];
            if (calories == 500)
                if (best_500_cal < score) best_500_cal = score;
        }
    }

    fclose(input);
    free(line);

    printf("Best score: %d\n", best_score);
    printf("Best 500 calories cookie: %d\n", best_500_cal);

    free(ingredient);

    return 0;
}

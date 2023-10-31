#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_FILE "day3.txt"

typedef struct {
    int x;
    int y;
} position;

typedef struct {
    position pos;
    size_t visits;
} house;

void check_alloc(void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
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

    size_t size = 1;
    position pos[2] = { 0 };

    house* houses = (house*) malloc (sizeof (house));
    check_alloc (houses);

    houses->pos.x = 0;
    houses->pos.y = 0;
    houses->visits = 1;

    int robo = 0;

    while (1)
    {
        char c = fgetc(input);
        if (feof(input)) break;

        if (c == '>') pos[robo].x++;
        if (c == '<') pos[robo].x--;
        if (c == '^') pos[robo].y--;
        if (c == 'v') pos[robo].y++;

        bool visited = false;
        int i = 0;
        for (; i < size; ++i)
            if (houses[i].pos.x == pos[robo].x && houses[i].pos.y == pos[robo].y)
            {
                visited = true;
                break;
            }
        if (visited)
            houses[i].visits++;
        else
        {
            houses = (house *) realloc (houses, sizeof (house) * (size + 1));
            check_alloc (houses);

            houses[size].pos.x = pos[robo].x;
            houses[size].pos.y = pos[robo].y;
            houses[size].visits = 1;
            size++;
        }
        // uncomment for part 2:
        // if (robo == 1) robo = 0; else robo = 1;
    }
    fclose(input);
    free(houses);

    printf("Visited houses: %ld\n", size);

    return 0;
}

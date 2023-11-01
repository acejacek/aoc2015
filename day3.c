#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_FILE "day3.txt"

typedef struct {
    int x;
    int y;
} position;

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

    position* houses = (position*) malloc (sizeof (position));
    check_alloc (houses);

    houses->x = 0;
    houses->y = 0;

    int robo = 0;
    char c;
    while ((c = fgetc(input)) != '\n') // whole file in oneliner
    {
        switch (c)
        {
          case '>':
            pos[robo].x++;
            break;
          case '<':
            pos[robo].x--;
            break;
          case '^':
            pos[robo].y--;
            break;
          case 'v':
            pos[robo].y++;
            break;
          default:
            fprintf(stderr, "Unknow direction %c %ld\n", c, size);
            exit(EXIT_FAILURE);
        }

        bool visited = false;
        int i = 0;
        for (; i < size; ++i)
            if (houses[i].x == pos[robo].x && houses[i].y == pos[robo].y)
            {
                visited = true;
                break;
            }
        if (!visited)
        {
            houses = (position *) realloc (houses, sizeof (position) * (++size));
            check_alloc (houses);

            houses[size - 1].x = pos[robo].x;
            houses[size - 1].y = pos[robo].y;
        }
        // uncomment for part 2:
        // if (robo == 1) robo = 0; else robo = 1;
    }
    fclose(input);
    free(houses);

    printf("Visited houses: %ld\n", size);

    return 0;
}

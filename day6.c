#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_FILE "day6.txt"

bool lights[1000][1000] = { false };

void set_lights(int x1, int y1, int x2, int y2, bool val)
{
    for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++)
            lights[x][y] = val;
}

void toggle_lights(int x1, int y1, int x2, int y2)
{
    for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++)
            lights[x][y] = !lights[x][y];
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
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;

        switch (line[6])
        {   
            case 'n':   // turn ON
                sscanf(line, "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2);
                //printf("Scanned: %d, %d, %d, %d\n", x1, y1, x2, y2);
                set_lights(x1, y1, x2, y2, true);
            break;

            case 'f':   // turn OFF
                sscanf(line, "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2);
                set_lights(x1, y1, x2, y2, false);
            break;

            case ' ':   // toggle            
                sscanf(line, "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2);
                toggle_lights(x1, y1, x2, y2);
            break;

            default:
                fprintf(stderr, "unknown command: %c\n", line[6]);
                exit(EXIT_FAILURE);  
        }
    }

    fclose(input);
    free(line);

    size_t number = 0;

    for (int x = 0; x < 1000; x++)
        for (int y = 0; y < 1000; y++)
            if (lights[x][y]) number++;

    printf("Number of lights lit: %zd\n", number);

    return 0;
}

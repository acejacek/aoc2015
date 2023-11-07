#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "day18.txt"

// edit for part #2

#define PART 1

typedef struct
{
    char* matrix;
    char* buffer;
    int rows;
    int width;
} Lights;

void check_alloc (void* p)
{
    if (p != NULL) return;

    fprintf (stderr, "Can't allocate memory!\n");
    exit (EXIT_FAILURE);
}

int count_neighbours (const Lights* lights, int row, int col)
{
    int sum = 0;
    for (int y = row - 1; y <= row + 1; ++y)
    {
        if (y < 0) continue;
        if (y == lights->rows) continue;

        for(int x = col - 1; x <= col + 1; ++x)
        {
            if (x < 0) continue;
            if (x == lights->width) continue;

            if (lights->matrix[(y * lights->width) + x] == '#')
                sum++;
        }
    }

    // ignore the cell under row/col
    if (lights->matrix[(row * lights->width) + col] == '#')
        sum--;

    return sum;
}

void update_lights (Lights* lights)
{
    for (int y = 0; y < lights->rows; ++y)
        for (int x = 0; x < lights->width; ++x)
            switch (count_neighbours(lights, y, x))
            {
                case 3:
                    lights->buffer[(lights->width * y) + x] = '#';
                    break;
                
                case 2:
                    lights->buffer[(lights->width * y) + x] = lights->matrix[(lights->width * y) + x];
                    break;

                default:
                    lights->buffer[(lights->width * y) + x] = '.';
            }
}

void swap_buffer (Lights* lights)
{
    char* tmp = lights->matrix;
    lights->matrix = lights->buffer;
    lights->buffer = tmp;
}

void lock_corner_lights (Lights* lights)
{
#if PART == 2
    lights->matrix[0] = '#';
    lights->matrix[lights->width - 1] = '#';
    lights->matrix[(lights->rows - 1) * lights->width] = '#';
    lights->matrix[(lights->rows - 1) * lights->width + lights->width - 1] = '#';
#endif
}

int count_lights(Lights* lights)
{
    int sum = 0;
    for (int i = 0; i < lights->rows * lights->width; ++i)
            if (lights->matrix[i] == '#')
                sum++;
    return sum;
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

    Lights lights;

    lights.matrix = NULL;
    lights.buffer = NULL;

    for (lights.rows = 0; (read = getline (&line, &len, input)) != -1; ++lights.rows)
    {
        lights.width = read - 1; // cut EOL
        lights.matrix = realloc (lights.matrix, sizeof(char) * lights.width * (lights.rows + 1));
        check_alloc (lights.matrix);
        memcpy (lights.matrix + lights.width * lights.rows, line, lights.width);
    }

    fclose (input);
    free (line);

    lights.buffer = malloc (sizeof(char) * lights.width * lights.rows);
    check_alloc (lights.buffer);

    lock_corner_lights (&lights);

    int const iterations = 100;

    for (int i = 0; i < iterations; ++i)
    {
        update_lights (&lights);
        swap_buffer (&lights);
        lock_corner_lights (&lights);
    }

    printf ("Lights on: %d\n", count_lights (&lights));
            
    free (lights.matrix);
    free (lights.buffer);

    return 0;
}

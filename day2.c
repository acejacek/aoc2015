#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "day2.txt"

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

    size_t total_area = 0;
    size_t ribbon = 0;

    while ((getline(&line, &len, input)) != -1)
    {
        int l, w, h;
        sscanf(line, "%dx%dx%d", &l, &w, &h);

        int first = l * w;
        int second = w * h;
        int third = h * l;

        int slack = first;
        if (slack > second) slack = second;
        if (slack > third) slack = third;

        total_area += 2 * first + 2 * second + 2 * third + slack;

        int bow = l * w * h;
        int longest = l;
        if (longest < w) longest = w;
        if (longest < h) longest = h;

        ribbon += bow + l + l + w + w + h + h - longest - longest;
    }

    fclose(input);
    free(line);

    printf("Total area of paper: %zd\n", total_area);
    printf("Total length of ribbon: %zd\n", ribbon);

    return 0;
}

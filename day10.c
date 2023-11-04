
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10000000

#define PUZZLE_INPUT "1321131112"
#define ITERATIONS 40

char sequence[MAX_LEN] = PUZZLE_INPUT;
char buffer[MAX_LEN];

void busy(void)
{
    static int i = 0;
    char spinner[4] = { '\\', '|', '/', '-' };
    printf("%c\b", spinner[i]);
    fflush(stdout);
    i = (i + 1) % 4;
}

void build_buffer(void)
{
    buffer[0] = '\0';
    int len = strlen(sequence);
    int i = 0;
    do
    {
        busy();   // So slow! I added busy indicator to show, that it's not hanged...
        int counter = 1;
        char x = sequence[i];

        for (; i + counter < len &&
                sequence[i + counter] == x;  ++counter);

        char step[3];
        sprintf(step, "%d%c", counter, x);
        strcat(buffer, step);

        i += counter;
    } while (i < len);
}

int main(void)
{
    for (int i = 0; i < ITERATIONS; ++i)
    {
        build_buffer();
        strcpy(sequence, buffer);
    }

    printf("Length: %zu\n", strlen(sequence));

    return 0;
}

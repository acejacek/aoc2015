#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "day14.txt"
#define TIME 2503

typedef enum { RUN, REST } State;

typedef struct
{
    char name[10];
    int speed;
    int flight_time;
    int rest_time;
    int state_time;
    State state;
    int distance;
    int points;
} Reindeer;

Reindeer* reindeer;

void check_alloc(void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
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
        reindeer = realloc(reindeer, sizeof(Reindeer) * (id + 1));
        check_alloc(reindeer);

        char change[5];
        sscanf(line, "%s %*s %*s %d %*s %*s %d seconds, but then must rest for %d",
                reindeer[id].name, 
                &reindeer[id].speed,
                &reindeer[id].flight_time,
                &reindeer[id].rest_time);

        reindeer[id].state_time = reindeer[id].flight_time;
        reindeer[id].state = RUN;
        reindeer[id].distance = 0;
        reindeer[id].points = 0;
    }

    fclose(input);
    free(line);

    for (int time = TIME; time > 0; time--)
    {
        int best_progress = 0;
        for (int i = 0; i < id; ++i)
        {
            switch(reindeer[i].state)
            {
                case RUN:
                    reindeer[i].distance += reindeer[i].speed;
                    if (--reindeer[i].state_time == 0)
                    {
                        reindeer[i].state = REST;
                        reindeer[i].state_time = reindeer[i].rest_time;
                    }
                    break;
                case REST:
                    if (--reindeer[i].state_time == 0)
                    {
                        reindeer[i].state = RUN;
                        reindeer[i].state_time = reindeer[i].flight_time;
                    }
                    break;
            }
            if (best_progress < reindeer[i].distance) best_progress = reindeer[i].distance;
        }

        for (int i = 0; i < id; ++i)         // award points to all with best progress
            if (best_progress == reindeer[i].distance)
                reindeer[i].points++;
    }

    int best_distance = 0;
    int best_points = 0;
    for (int i = 0; i < id; ++i)
    {
        if (best_distance < reindeer[i].distance) best_distance = reindeer[i].distance;
        if (best_points < reindeer[i].points) best_points = reindeer[i].points;
    }

    printf("Best distance: %d\n", best_distance);
    printf("Best points: %d\n", best_points);

    free(reindeer);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "day9.txt"

struct City;

typedef struct Route {
    struct City* destination;
    int distance;
    struct Route* next;
} Route;

typedef struct City {
    char name[20];
    Route* route;
    int visited;
} City;
    
typedef struct Graph {
    City* city;
    int elements;
} Graph;

Graph* graph = NULL;

void check_alloc(void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
}

int are_all_cities_visited(void)
{
    if (graph == NULL) return 0;

    for (int i = 0; i < graph->elements; ++i)
        if (graph->city[i].visited == 0) return 0;

    return 1;
}

void add_city(char* name, char* dest, int dist)
{
    if (graph == NULL)
    {
        graph = (Graph *) malloc (sizeof(Graph));
        check_alloc(graph);
        graph->elements = 0;
    }

    for (int i = 0; i < graph->elements; ++i)
    {
        if (strcmp(graph->city[i].name, name) == 0)
        {
            // check, if this dest exists
            Route* r = graph->city[i].route;
            if (r == NULL)
            {
            }

        } 
    }
        


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

    while ((getline(&line, &len, input)) != -1)
    {
        char from[20];
        char to[20];
        int dist;

        sscanf(line, "%s %*s %s %*s %d", from, to, &dist);
       
        printf("%s, %s, %d\n", from, to, dist);
        break; 
    }

    fclose(input);
    free(line);
    free(graph);

    // printf("Total length of ribbon: %zd\n", ribbon);

    return 0;
}

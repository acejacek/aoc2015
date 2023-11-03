#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define INPUT_FILE "day9.txt"

typedef struct Route {
    char city_a[20];
    char city_b[20];
    int distance;
} Route;

typedef struct City {
    char name[20];
    bool visited;
} City;

Route* route = NULL;
int routes = 0;

City* city = NULL;
int cities = 0;

int shortest_distance = INT_MAX;
int longest_distance = 0;

void check_alloc(void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
}

void add_city(char* name)
{
    for (int i = 0; i < cities; ++i)
        if (strcmp(city[i].name, name) == 0) return; // already in list

    city = realloc(city, sizeof(City) * ++cities);
    check_alloc(city);
    city[cities - 1].visited = false;
    strcpy(city[cities - 1].name, name);
}

bool all_cities_visited(void)
{
    for (int i = 0; i < cities; ++i)
        if (! city[i].visited) return false;

    return true;
}

void visit(char* name, int distance)
{
    int i = 0;
    for (; i < cities && (strcmp(city[i].name, name) != 0); ++i);
    if (i == cities)
    {
        fprintf(stderr, "Cant find city %s in list.\n", name);
        exit(EXIT_FAILURE);
    }

    if (city[i].visited) return;

    city[i].visited = true;

    if (all_cities_visited())
    {
        if (shortest_distance > distance) shortest_distance = distance;
        if (longest_distance < distance) longest_distance = distance;
    }
    else
    {
        for (int j = 0; j < routes; ++j)
            if (strcmp(route[j].city_a, city[i].name) == 0)
                visit(route[j].city_b, distance + route[j].distance);
    }

    city[i].visited = false;
    return;
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
        route = realloc(route, sizeof(Route) * (++routes)); 
        check_alloc(route);

        sscanf(line, "%s %*s %s %*s %d",
                route[routes - 1].city_a, route[routes - 1].city_b, &route[routes - 1].distance);
       
        add_city(route[routes - 1].city_a);
        add_city(route[routes - 1].city_b);

        route = realloc(route, sizeof(Route) * (++routes));  // add symmetric route in opposite direction
        check_alloc(route);

        strcpy(route[routes - 1].city_a, route[routes - 2].city_b);
        strcpy(route[routes - 1].city_b, route[routes - 2].city_a);
        route[routes - 1].distance = route [routes - 2].distance;
    }

    fclose(input);
    free(line);

    for (int i = 0; i < cities; ++i)           // start recurrently from all cities
        visit(city[i].name, 0);

    free(route);
    free(city);

    printf("Shortest distance: %d\n", shortest_distance);
    printf("Longest distance: %d\n", longest_distance);

    return 0;
}

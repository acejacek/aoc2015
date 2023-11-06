#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INPUT_FILE "day16.txt"

enum Facts { CHILDREN, CATS, SAMOYEDS, POMERANIANS, AKITAS, VIZSLAS, GOLDFISH, TREES, CARS, PERFUMES };

bool is_right_sue(int* person)
{
    if (person[CHILDREN] != 3 && person[CHILDREN] >= 0) return false;
    if (person[CATS] != 7 && person[CATS] >= 0) return false;
    if (person[SAMOYEDS] != 2 && person[SAMOYEDS] >= 0) return false;
    if (person[POMERANIANS] != 3 && person[POMERANIANS] >= 0) return false;
    if (person[AKITAS] != 0 && person[AKITAS] >= 0) return false;
    if (person[VIZSLAS] != 0 && person[VIZSLAS] >= 0) return false;
    if (person[GOLDFISH] != 5 && person[GOLDFISH] >= 0) return false;
    if (person[TREES] != 3 && person[TREES] >= 0) return false;
    if (person[CARS] != 2 && person[CARS] >= 0) return false;
    if (person[PERFUMES] != 1 && person[PERFUMES] >= 0) return false;

    return true;
}

bool is_really_right_sue(int* person)
{
    if (person[CHILDREN] != 3 && person[CHILDREN] >= 0) return false;
    if (person[CATS] <= 7 && person[CATS] != -1) return false;
    if (person[SAMOYEDS] != 2 && person[SAMOYEDS] >= 0) return false;
    if (person[POMERANIANS] >= 3 && person[POMERANIANS] != -1) return false;
    if (person[AKITAS] != 0 && person[AKITAS] >= 0) return false;
    if (person[VIZSLAS] != 0 && person[VIZSLAS] >= 0) return false;
    if (person[GOLDFISH] >= 5 && person[GOLDFISH] != -1) return false;
    if (person[TREES] <= 3 && person[TREES] != -1) return false;
    if (person[CARS] != 2 && person[CARS] >= 0) return false;
    if (person[PERFUMES] != 1 && person[PERFUMES] >= 0) return false;

    return true;
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
    int part1 = 0;
    int part2 = 0;

    for (id = 0; (read = getline(&line, &len, input)) != -1; ++id)
    {
        char param[3][15];
        int val[3];

        sscanf(line, "%*s %*s %s %d, %s %d, %s %d",
                param[0], val, param[1], val + 1, param[2], val + 2);

        int sue[10] = { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1};
        
        for (int i = 0; i < 3; ++i)
        {
            if (strcmp(param[i], "children:") == 0)
                sue[CHILDREN] = val[i];
            else if  (strcmp(param[i], "cats:") == 0)
                sue[CATS] = val[i];
            else if  (strcmp(param[i], "samoyeds:") == 0)
                sue[SAMOYEDS] = val[i];
            else if  (strcmp(param[i], "pomeranians:") == 0)
                sue[POMERANIANS] = val[i];
            else if  (strcmp(param[i], "akitas:") == 0)
                sue[AKITAS] = val[i];
            else if  (strcmp(param[i], "vizslas:") == 0)
                sue[VIZSLAS] = val[i];
            else if  (strcmp(param[i], "goldfish:") == 0)
                sue[GOLDFISH] = val[i];
            else if  (strcmp(param[i], "trees:") == 0)
                sue[TREES] = val[i];
            else if  (strcmp(param[i], "cars:") == 0)
                sue[CARS] = val[i];
            else if  (strcmp(param[i], "perfumes:") == 0)
                sue[PERFUMES] = val[i];
            else
            {
                fprintf(stderr, "Unknown parameter %s\n", param[i]);
                exit(1);
            }
        }

        if (is_right_sue(sue)) part1 = id + 1;
        if (is_really_right_sue(sue)) part2 = id + 1;
    }

    fclose(input);
    free(line);

    if (part1) 
        printf("Part 1: %d\n", part1);
    else printf("Not found...\n");

    if (part2) 
        printf("Part 2: %d\n", part2);
    else printf("Not found...\n");

    return 0;
}

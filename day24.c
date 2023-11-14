#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define PACKAGES_COUNT 28

typedef struct
{
//    int package[PACKAGES];
    int count;
    int weight;
    size_t qe;
} Group;

bool distribute(int* p, Group* groups, const int target_weight)
{
    for (int i = 0; i < 3; ++i)
    {
        groups[i].count = 0;
        groups[i].weight = 0;
    }
    groups[0].qe = 1;

    int g;
    for (int i = 0; i < PACKAGES_COUNT; ++i)
    {
        g = rand() % 3;
    
        groups[g].weight += p[i];
        if (groups[g].weight > target_weight)
            return false;                      // no point to continue

        groups[g].count++;

        if (g == 0) groups[0].qe *= p[i];
    }
    return true;
}

int main(void)
{
    srand(time(NULL));

//    int packages[PACKAGES_COUNT] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 11 };
    int packages[PACKAGES_COUNT] = {
        1,
        3,
        5,
        11,
        13,
        17,
        19,
        23,
        29,
        31,
        41,
        43,
        47,
        53,
        59,
        61,
        67,
        71,
        73,
        79,
        83,
        89,
        97,
        101,
        103,
        107,
        109,
        113
    };

    int target_weight = 0;
    for (int i = 0; i < PACKAGES_COUNT; ++i)
        target_weight += packages[i];

    target_weight /= 3;

    printf("Target: %d\n", target_weight);

    Group groups[3];

    size_t min_qe = SIZE_MAX;
    int min_count = INT_MAX;

    for (size_t i = 0; i < 1000; ++i)
    {
        while (1)
        {
            if (! distribute(packages, groups, target_weight)) continue;

            // weight
            if (groups[0].weight != target_weight) continue;

            // quantity
            if (groups[0].count > groups[1].count) continue;
            if (groups[0].count > groups[2].count) continue;

            if (min_count >= groups[0].count) break;
        }

        min_count = groups[0].count;

        if (min_qe > groups[0].qe)
        {
            min_qe = groups[0].qe;
            printf("%ld\n", min_qe);
        }
    }
    
    printf("Minimum quantum entanglement is: %ld\n", groups[0].qe);

    return 0;
}


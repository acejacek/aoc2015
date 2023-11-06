#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int volume;
    int nr_of_containers;
    int counter;
    int minimum_mix;
    int minimum_counter;
} Params;

void combine(int* containers, int* mix, const int mix_size, const int i, Params* params)
{
    if (i == mix_size)
    {   
        int sum = 0;
        for (int j = 0; j < mix_size; ++j)
                sum += mix[j];
        if (sum == params->volume)
        {
            params->counter++;
            if (params->minimum_mix >= mix_size)
            {
                params->minimum_mix = mix_size;
                params->minimum_counter++;
            }
        }
        return;
    }
    while (containers[0])  // breaks at 0 terminator
    {
        mix[i] = containers[0];
        combine(++containers, mix, mix_size, i + 1, params);
    }
}

int main(void)
{
    Params params;

    params.nr_of_containers = 20;
    params.volume = 150;
    params.counter = 0;
    params.minimum_mix = INT_MAX;
    params.minimum_counter = 0;

    int containers[21] = {11,30,47,31,32,36,3,1,5,3,32,36,15,11,46,26,28,1,19,3,0};// 0 = terminator

    for (int i = 1; i <= params.nr_of_containers; ++i) // possible mix sizes
    {
        int mix[i];
        combine(containers, mix, i, 0, &params);
    }

    printf("Combinations: %d\n", params.counter);
    printf("Combinations: %d (for minimum number of %d containers).\n", params.minimum_counter, params.minimum_mix);

    return 0;
}

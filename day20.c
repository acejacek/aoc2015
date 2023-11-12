#include <stdio.h>
#include <stdlib.h>

#define TARGET_PRESENTS 34000000

size_t number_or_presents1(size_t house)
{
    size_t presents = 0;
    for (size_t i = 1; i * i <= house; ++i)
        if (house % i == 0)
        {
            presents += 10 * i;

            if (house == i * i) break;

            // second divisor
            presents += 10 * (house / i);
        }
    return presents;
}

size_t number_or_presents2(size_t house)
{
    size_t presents = 0;
    for (size_t i = 1; i * i <= house; ++i)
        if (house % i == 0)
        {
            if (i * 50 >= house)
                presents += 11 * i;

            if (house == i * i) break;
            
            size_t second_divisor = house / i;
            if (second_divisor * 50 >= house) 
                presents += 11 * second_divisor;
        }
    return presents;
}
int main(void)
{
/*
 * possible speedup ideas:
 * 1. change step to 2
 * 2. start from house 100.000
 * 3. test, if house dividable by 2, 3, and other primes
 */

    size_t i;
    for (i = 2; number_or_presents1(i) < TARGET_PRESENTS; ++i);

    printf("Lowest house number id: %zu\n", i);

    for (i = 2; number_or_presents2(i) < TARGET_PRESENTS; ++i);

    printf("Lowest house number id in part 2: %zu\n", i);
    return 0;
}


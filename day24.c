/* Naive algorithm
 * goes through the list of elements and works out all possible combinations
 * Performance on i5-6500T CPU @ 2.5 GHz:
 * case #1 takes 1 min 16 sek
 * case #2 takes 36 min.
 * The initial results are visible much earlier.
 * Calculation is for program to run through all posibilities
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define GROUPS 4
//#define TEST

#ifdef TEST
#define PACKAGES_COUNT 10
#else
#define PACKAGES_COUNT 28
#endif

typedef struct {
    size_t weight;
    bool taken;
} Packages;

typedef struct list_t {
    size_t package;
    struct list_t* next;
} List;

List* head[GROUPS] = { NULL };
size_t sum[GROUPS] = { 0 };
size_t count = 0;

size_t min_count = SIZE_MAX;
size_t min_qe = SIZE_MAX;

void llist_push(size_t group, size_t weight)
{
    List* new = malloc(sizeof(*new));
    if (!new) exit(1);
    
    new->package = weight;
    if (head[group])
        new->next = head[group];
    else
        new->next = NULL;

    head[group] = new;

    if (group == 0) ++count;
}

void llist_pop(size_t group)
{
    if (!head[group]) return;

    List* next = head[group]->next;
    free(head[group]);
    head[group] = next;

    if (group == 0) --count;
}

void llist_print(size_t group)
{
    for (List* l = head[group]; l != NULL; l = l->next)
        printf("%zu ", l->package);
    putchar('\n');
}

// calculate quantum entanglement
size_t llist_qe(void)
{
    size_t qe = 1;
    for (List* l = head[0]; l != NULL; l = l->next)
        qe *= l->package;

    return qe;
}

void distribute(Packages* p, const size_t target_weight, const size_t start, const size_t group)
{
    if (sum[group] == target_weight)
    {
        if (group == GROUPS - 2)  // I don't need to calculate last group. If first 2 (or 3) are ok, last is also OK.
        {
            // Now I have all groups set, check, if they are best
            if (min_count > count)
            {
                min_count = count; // new minimal amount of items in group 0
                min_qe = SIZE_MAX; // reset QE
            }
            
            if (min_count == count)
            {
                // recalculate QE, maybe it's better than last time
                size_t qe = llist_qe();
                if (min_qe > qe)
                {
#ifdef TEST
                    for (size_t i = 0; i < GROUPS; ++i)
                    {
                        printf("Group %zu: ", i + 1);
                        llist_print(i);
                    }
#endif
                    min_qe = qe;
                    printf("New minimum QE: %zu\n", min_qe);
                }
            }
            return;
        }

        if (count <= min_count)    // otherwise there is no point to search more
            distribute(p, target_weight, 0, group + 1);  // this group is fine, search for next one
                                                         
        return; 
    }

    /* Main part of this function.
     * Take one element, add it to the list and make the element unavailable for other lists.
     * Check if list fulfills criteria, if yes, recurently run this part until all lists
     * are populated with correct data. Then remove elemen from the list and put there next one. Repeat.
     */
    for (size_t i = start; i < PACKAGES_COUNT; ++i)
    {
        if (p[i].taken) continue;

        sum[group] += p[i].weight;

        if (sum[group] <= target_weight)  // not exceding target weight, continue recursion
        {
            llist_push(group, p[i].weight);
            p[i].taken = true;
            distribute(p, target_weight, i + 1, group);
            p[i].taken = false;
            llist_pop(group);
        }

        sum[group] -= p[i].weight;
    }
}

int main(void)
{
#ifdef TEST
    size_t p[PACKAGES_COUNT] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 11 };
#else
    size_t p[PACKAGES_COUNT] = {
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
        113,
    };
#endif

    Packages packages[PACKAGES_COUNT];

    size_t target_weight = 0;
    for (int i = PACKAGES_COUNT - 1; i >= 0; --i)  // load big first
    {
        target_weight += p[i];
        packages[i].weight = p[i];
        packages[i].taken = false;
    }

    target_weight /= GROUPS;
    printf("Target: %zu\n", target_weight);

    distribute(packages, target_weight, 0, 0);

    printf("Done.\n");
    return 0;
}


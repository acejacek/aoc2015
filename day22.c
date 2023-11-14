#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define BOSS_HIT_POINTS 58
#define BOSS_DAMAGE 9

// change for part 2:
#define PART 1

enum { PLAYER, BOSS, TRUCE, UNDEFINED };

typedef struct
{
    int hit_points;
    int damage;
    int armor;
    int cost;
    int mana;
    int shield_active;
    int recharge_active;
    int poison_active;
} Character;

bool is_dead(const Character* a)
{
    return (a->hit_points > 0) ? false : true;
}

bool cast_misille(Character* a, Character* b)
{
    const int cost = 53;
    if (a->mana < cost) return false;

    a->mana -= cost;
    b->hit_points -= 4;
    a->cost += cost;

    return true;
}

bool cast_drain(Character* a, Character* b)
{
    const int cost = 73;
    if (a->mana < cost) return false;

    a->mana -= cost;
    b->hit_points -= 2;
    a->hit_points += 2;
    a->cost += cost;

    return true;
}

bool cast_shield(Character* a, Character* b)
{
    if (a->shield_active) return false;

    const int cost = 113;
    if (a->mana < cost) return false;

    a->mana -= cost;
    a->shield_active = 6;
    a->cost += cost;

    return true;
}

bool cast_poison(Character* a, Character* b)
{
    if (a->poison_active) return false;

    const int cost = 173;
    if (a->mana < cost) return false;

    a->mana -= cost;
    a->poison_active = 6;
    a->cost += cost;

    return true;
}

bool cast_recharge(Character* a, Character* b)
{
    if (a->recharge_active) return false;

    const int cost = 229;
    if (a->mana < cost) return false;

    a->mana -= cost;
    a->recharge_active = 5;
    a->cost += cost;

    return true;
}

bool apply_active_spells(Character* a, Character* b)
{
    if (a->poison_active)
    {
        a->poison_active--;
        b->hit_points -= 3;
        if (is_dead(b)) return true;
    }

    if (a->shield_active)
    {
        a->shield_active--;
        a->armor = 7;
    }
    else
        a->armor = 0;

    if (a->recharge_active)
    {
        a->recharge_active--;
        a->mana += 101;
    }

    return false;
}

bool fight(const Character* a, Character* b)
{
    int attack_force = a->damage - b->armor;

    if (attack_force > 0)
        b->hit_points -= attack_force;
    else
        b->hit_points--;

    if (is_dead(b)) return true;

    return false;
}

void busy(void)
{
    static int i = 0;
    char spinner[4] = { '\\', '|', '/', '-' };
    printf("%c\b", spinner[i]);
    fflush(stdout);
    i = (i + 1) % 4;
}

int duel(Character* player, Character* boss, const int min_cost)
{
    player->hit_points = 50;
    player->mana = 500;
    player->armor = 0;
    player->cost = 0;
    player->shield_active = 0;
    player->recharge_active = 0;
    player->poison_active = 0;

    boss->hit_points = BOSS_HIT_POINTS;

    bool (*spell[5])(Character*, Character*);

    spell[0] = &cast_misille;
    spell[1] = &cast_drain;
    spell[2] = &cast_shield;
    spell[3] = &cast_poison;
    spell[4] = &cast_recharge;

    while (true)
    {
        // player turn
#if PART == 2
        player->hit_points--;
        if (is_dead(player)) return BOSS;
#endif
        // apply active spells
        if (apply_active_spells(player, boss)) return PLAYER;

        // player cast a [random] spell
        int cast_nr = rand() % 5;
        int orig_cast_nr = cast_nr;
        while (!spell[cast_nr](player, boss))   // unsucesfull
        {
            cast_nr++;
            cast_nr %= 5;                       // round to 0 after 4
            if (cast_nr == orig_cast_nr)        // can't cast any spell
                return BOSS;
        }

        if (player->cost >= min_cost) return TRUCE;  // no point to continue 
                                                     
        if (is_dead(boss)) return PLAYER;

        // boss turn
        // apply active spells
        if (apply_active_spells(player, boss)) return PLAYER;
        // boss attacks
        if (fight(boss, player)) return BOSS;

    }

    return UNDEFINED;
}

int main(void)
{
    srand(time(NULL));

    Character boss = { 0 };
    boss.damage = BOSS_DAMAGE;
    boss.armor = 0;

    Character player = { 0 };

    int min_cost = INT_MAX;

    for (size_t i = 0; i < 10000000; ++i)             // brute force
    {
        if (i % 100000 == 0) busy();
        if (duel(&player, &boss, min_cost) == PLAYER)
            if (min_cost > player.cost) min_cost = player.cost;
    }
    printf("The least amount of mana to beat the boss is: %d\n", min_cost);

    return 0;
}


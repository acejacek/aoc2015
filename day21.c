#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define BOSS_HIT_POINTS 100
#define BOSS_DAMAGE 8
#define BOSS_ARMOR 2

enum { PLAYER, BOSS };

typedef struct
{
    int cost;
    int damage;
    int armor;
} Equipment;

typedef struct
{
    int hit_points;
    int damage_score;
    int armor_score;
    int cost;
    Equipment weapon;
    Equipment plates;
    Equipment ring_l;
    Equipment ring_r;
} Character;

void fight(Character* a, Character* b)
{
    int attack_force = a->damage_score - b->armor_score;

    if (attack_force > 0)
        b->hit_points -= attack_force;
    else
        b->hit_points--;
}

bool is_dead(Character* a)
{
    return (a->hit_points > 0) ? false : true;
}

void calculate_damage(Character* a)
{
    a->damage_score =
        a->weapon.damage 
        + a->ring_l.damage
        + a->ring_r.damage;
}

void calculate_armor(Character* a)
{
    a->armor_score =
        a->plates.armor
        + a->ring_l.armor
        + a->ring_r.armor;
}

void calculate_cost(Character* a)
{
    a->cost = a->weapon.cost 
        + a->plates.cost
        + a->ring_l.cost
        + a->ring_r.cost;
}

int duel(Character* player, Character* boss)
{
    player->hit_points = 100;
    boss->hit_points = BOSS_HIT_POINTS;
    calculate_cost(player);
    calculate_armor(player);
    calculate_damage(player);

    int turn = PLAYER;
    do
        if (turn == PLAYER)
        {
            fight(player, boss);
            if (is_dead(boss)) break;
            turn = BOSS;
        }
        else
        {
            fight(boss, player);
            if (is_dead(player)) break;
            turn = PLAYER;
        }
    while (1);

    return turn;
}

int main(void)
{
    Equipment e[19] = { 0 };
    // weapons:
    e[0].cost = 8;
    e[0].damage = 4;
    e[0].armor = 0;

    e[1].cost = 10;
    e[1].damage = 5;
    e[1].armor = 0;

    e[2].cost = 25;
    e[2].damage = 6;
    e[2].armor = 0;

    e[3].cost = 40;
    e[3].damage = 7;
    e[3].armor = 0;

    e[4].cost = 74;
    e[4].damage = 8;
    e[4].armor = 0;

    // armors
    e[5].cost = 0;       // no armor
    e[5].damage = 0;
    e[5].armor = 0;

    e[6].cost = 13;
    e[6].damage = 0;
    e[6].armor = 1;

    e[7].cost = 31;
    e[7].damage = 0;
    e[7].armor = 2;

    e[8].cost = 53;
    e[8].damage = 0;
    e[8].armor = 3;

    e[9].cost = 75;
    e[9].damage = 0;
    e[9].armor = 4;

    e[10].cost = 102;
    e[10].damage = 0;
    e[10].armor = 5;

    // rings
    e[11].cost = 0;    // no ring
    e[11].damage = 0;
    e[11].armor = 0;

    e[12].cost = 25;
    e[12].damage = 1;
    e[12].armor = 0;

    e[13].cost = 50;
    e[13].damage = 2;
    e[13].armor = 0;

    e[14].cost = 100;
    e[14].damage = 3;
    e[14].armor = 0;

    e[15].cost = 20;
    e[15].damage = 0;
    e[15].armor = 1;

    e[16].cost = 40;
    e[16].damage = 0;
    e[16].armor = 2;

    e[17].cost = 80;
    e[17].damage = 0;
    e[17].armor = 3;

    e[18].cost = 0;    // no ring, again, for other hand
    e[18].damage = 0;
    e[18].armor = 0;

    Character boss;
    boss.damage_score = BOSS_DAMAGE;
    boss.armor_score = BOSS_ARMOR;
    
    Character player = { 0 };

    int min_cost = INT_MAX;
    int max_cost = 0;

    for (int w = 0; w < 5; ++w)  // weapons
    {
        player.weapon = e[w];

        for (int a = 5; a < 11; ++a) // armor
        {
            player.plates = e[a];

            for (int lr = 11; lr < 18; ++lr) // left ring
            {
                player.ring_l = e[lr];

                for (int rr = 11; rr < 19; ++rr) // right ring
                {
                    if (rr == lr) continue; // can have same element on both hands

                    player.ring_r = e[rr];

                    if (duel(&player, &boss) == PLAYER)
                    {
                        if (min_cost > player.cost) min_cost = player.cost;
                    }
                    else
                        if (max_cost < player.cost) max_cost = player.cost;
                }
            }
        }
    }

    printf("Minimal cost to beat the boss is: %d\n", min_cost);
    printf("Maximal  cost to lose against the boss is: %d\n", max_cost);

    return 0;
}


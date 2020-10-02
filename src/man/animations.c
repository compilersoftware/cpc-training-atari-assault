#include "animations.h"
#include <cpctelera.h>
#include "sprites/enemy1.h"


const AnimFrame_t man_animations_enemy1Animation[] = {
    {12, {.sprite = spriteEnemy1_0}}, // Ojo: sintaxis de asignación a miembros concretos de una estructura
    {12, {.sprite = spriteEnemy1_1}},
    {0, {.next = man_animations_enemy1Animation}}
};

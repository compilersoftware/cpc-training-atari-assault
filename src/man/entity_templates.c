#include "entity_templates.h"

#include <man/animations.h>
#include <man/entity.h>
#include <sprites/enemy1.h>
#include <sprites/mothership.h>
#include <sprites/playership.h>
#include <sys/ai.h>

const Entity_t mothershipTemplate = {
    entityTypeMovable | entityTypeRenderable | entityTypeAI,
    38, 10,                                                  
    SPRITEMOTHERSHIP_W,  SPRITEMOTHERSHIP_H, 
    -1,  0,                                
    spriteMothership,                       
    sys_ai_mothershipBehaviour,
    0x0000, 0x00             
};

const Entity_t enemy1Template = {
    entityTypeMovable | entityTypeRenderable | entityTypeAI | entityTypeAnimated,
    0, 40,
    SPRITEENEMY1_0_W,  SPRITEENEMY1_0_H,
    0,  0,
    spriteEnemy1_0,
    sys_ai_leftRightBehaviour,
    man_animations_enemy1Animation, MAN_ANIMATIONS_ENEMY_1_ANIMATION_TIME
};

const Entity_t scoreboardPlayerTemplate = {
    entityTypeRenderable,
    0, 192,
    SPRITEPLAYESHIP_1_W,  SPRITEPLAYESHIP_1_H,
    0,  0,
    spritePlayeship_1,
    0x0000,
    0x0000, 0x00
};

const Entity_t playerTemplate = {
    entityTypeMovable | entityTypeRenderable | entityTypeControllable,
    38, 180,                   
    SPRITEPLAYESHIP_0_W,  SPRITEPLAYESHIP_0_H,  
    0,  0,    
    spritePlayeship_0,                      
    0x0000,
    0x0000, 0x00
};

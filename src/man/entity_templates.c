#include "entity_templates.h"

#include <man/animations.h>
#include <man/entity.h>
#include <sprites/enemy1.h>
#include <sprites/mothership.h>
#include <sprites/playership.h>
#include <sprites/vshot.h>
#include <sys/ai.h>

const Entity_t mothershipTemplate = {
    entityTypeMothership,
    entityComponentMovement | entityComponentRender | entityComponentAi,
    38, 10,                                                  
    SPRITEMOTHERSHIP_W,  SPRITEMOTHERSHIP_H, 
    -1,  0,                                
    spriteMothership,                       
    sys_ai_mothershipBehaviour,
    0,
    0x0000, 0x00             
};

const Entity_t enemy1Template = {
    entityTypeEnemy,
    entityComponentMovement | entityComponentRender | entityComponentAi | entityComponentAnimation,
    0, LANE_2_Y,
    SPRITEENEMY1_0_W,  SPRITEENEMY1_0_H,
    0,  0,
    spriteEnemy1_0,
    sys_ai_enemyBehaviour,
    0,
    man_animations_enemy1Animation, MAN_ANIMATIONS_ENEMY_1_ANIMATION_TIME
};

const Entity_t scoreboardPlayerTemplate = {
    entityTypePlayer,
    entityComponentRender,
    0, 192,
    SPRITEPLAYESHIP_1_W,  SPRITEPLAYESHIP_1_H,
    0,  0,
    spritePlayeship_1,
    0x0000,
    0,
    0x0000, 0x00
};

const Entity_t playerTemplate = {
    entityTypeDefault,
    entityComponentMovement | entityComponentRender | entityComponentInput,
    38, PLAYER_Y,                   
    SPRITEPLAYESHIP_0_W,  SPRITEPLAYESHIP_0_H,  
    0,  0,    
    spritePlayeship_0,                      
    0x0000,
    0,
    0x0000, 0x00
};

const Entity_t playerShotTemplate = {
    entityTypeShot,
    entityComponentMovement | entityComponentRender | entityComponentAi,
    0, PLAYERSHOT_Y,
    SPRITEVSHOT_W,  SPRITEVSHOT_H,
    0,  -8,
    spriteVShot,
    sys_ai_autodestroyBehaviour,
    14,
    0x0000, 0x00
};
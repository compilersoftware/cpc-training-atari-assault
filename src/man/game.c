#include "game.h"
#include "man/entity.h"
#include "sys/physics.h"
#include "sys/render.h"
#include "sys/ai.h"
#include "sprites/mothership.h"
#include "sprites/playership.h"
#include "sprites/enemy1.h"
#include "sys/animations.h"
#include "man/animations.h"

/* Atributos privados */

u8 m_enemyOnLane;

const u8 sprite[] = {
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00
};

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
    man_animations_enemy1Animation, 0x00
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


/* Funciones privadas */

Entity_t* m_man_game_createTemplateEntity(const Entity_t* template)
{
    Entity_t* entity = man_entity_create();
    cpct_memcpy(entity, template, sizeof(Entity_t));
    return entity;
}


/* Funciones públicas */

void man_game_init()
{
    // En C < C11 hay que declarar las variables al principio del ámbito (scope)
    Entity_t* entity;

    // Inicializar sistemas
    sys_render_init();

    // Inicializar manager
    man_entity_init();

    // Mothership
    m_man_game_createTemplateEntity(&mothershipTemplate);

    // Marcador
    // La forma "clásica" de escribir esto sería con un bucle for, pero esta manera es
    // más óptima, ya que vemos claramente que el valor máximo de x es 30 y que saldrá
    // del bucle cuando x llegue a 0, que es una comparación muy sencilla para el procesador
    {
        u8 x = 30;
        do {
            entity = m_man_game_createTemplateEntity(&scoreboardPlayerTemplate);
            x -= 10;
            entity->x = x;
        } while (x != 0);
    }

    // Player
    m_man_game_createTemplateEntity(&playerTemplate);

    // Flag de carril de creación de enemigos ocupado
    m_enemyOnLane = 0;
}

void man_game_play()
{
    while(1) {

        // Actualizar sistemas
        sys_ai_update();
        sys_physics_update();
        sys_animations_update();
        sys_render_update();

        // Actualizar manager
        man_entity_update();

        //cpct_waitHalts(5);
        cpct_waitVSYNC;
    }
}

/**
 * @precondition mothership es una entidad mothership
 */
void man_game_createEnemy(Entity_t* mothership)
{
    // Si ya hay un enemigo en este carril, no creamos uno nuevo
    if (m_enemyOnLane) {
        return;
    }

    // Creamos un nuevo enemigo
    {
        Entity_t* enemy = m_man_game_createTemplateEntity(&enemy1Template);
        // Lo colocamos en la misma posición que la madre nodriza pero centrado
        enemy->x = mothership->x + (SPRITEMOTHERSHIP_W - SPRITEENEMY1_0_W) / 2;
        enemy->vx = mothership->vx;
    }

    // Marcamos que el carril está ocupado
    m_enemyOnLane = 1;
}

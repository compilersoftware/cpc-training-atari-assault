#include "game.h"

#include <man/animations.h>
#include <man/entity.h>
#include <man/entity_templates.h>
#include <sprites/enemy1.h>
#include <sprites/mothership.h>
#include <sprites/playership.h>
#include <sys/ai.h>
#include <sys/animations.h>
#include <sys/physics.h>
#include <sys/render.h>

/* Atributos privados */

u8 m_laneStatus[3];

/* Funciones privadas */

void m_man_game_wait(u8 n)
{
    do {
        cpct_waitHalts(2);
        cpct_waitVSYNC();
    } while (--n);
}

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

    // Flags de estado de carriles
    cpct_memset(m_laneStatus, 0, sizeof(m_laneStatus));
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

        m_man_game_wait(2);
        cpct_waitVSYNC;
    }
}

/**
 * @precondition mothership es una entidad mothership
 */
void man_game_createEnemy(Entity_t* mothership)
{
    // Si ya hay un enemigo en este carril, no creamos uno nuevo
    if (m_laneStatus[2] != 0) {
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
    m_laneStatus[2] = 1;
}

/**
 * @precondition enemy es una entidad enemy
 */
void man_game_enemyLaneDown(Entity_t* enemy)
{
    if (enemy->y > LANE_1_Y) {
        // Estamos en el carril 0 y no se puede bajar más
        return;
    }

    {
        u8 lane = 2;
        if (enemy->y > LANE_2_Y) {
            lane = 1;
        }

        // Comprobamos si el carril inferior está ocupado
        if (m_laneStatus[lane - 1] != 0) {
            return;
        }

        // Bajamos al carril inferior
        enemy->y += LANE_DY;
        // Actualizamos el estado de los carriles
        m_laneStatus[lane] = 0;
        m_laneStatus[lane - 1] = 1;
    }
}

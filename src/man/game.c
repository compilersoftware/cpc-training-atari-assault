#include "game.h"

#include <man/animations.h>
#include <man/entity.h>
#include <man/entity_templates.h>
#include <sprites/enemy1.h>
#include <sprites/mothership.h>
#include <sprites/playership.h>
#include <sys/ai.h>
#include <sys/animations.h>
#include <sys/collisions.h>
#include <sys/physics.h>
#include <sys/render.h>

/* Atributos privados */

u8 m_laneStatus[3];
u8 m_playerShot;

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

/**
 * @precondition enemy es una entidad enemy
 */
u8 m_man_game_getEnemyLane(Entity_t* enemy)
{
    u8 enemyY = enemy->y;
    switch (enemyY) {
        case LANE_0_Y: 
            return 0;
        case LANE_1_Y:
            return 1;
        default:
            return 2;
    }
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

    // Flag de estado de disparo de jugador
    m_playerShot = 0;
}

void man_game_play()
{
    while(1) {

        // Actualizar sistemas
        sys_ai_update();
        sys_physics_update();
        sys_animations_update();
        sys_collisions_update();
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
    u8 lane = m_man_game_getEnemyLane(enemy);
    Entity_t* enemyClone;

    if (lane == 0) {
        return;
    }

    // Comprobamos si el carril inferior está ocupado
    if (m_laneStatus[lane - 1] != 0) {
        return;
    }

    // Clonamos la entidad para luego destruirla y así conseguir que se
    // "borre el rastro"
    enemyClone = man_entity_clone(enemy);
    // Sólo queremos que se dibuje, no que se actualice la posición ni nada
    enemyClone->components = entityComponentRender;
    man_entity_markForDestruction(enemyClone);

    // Bajamos al carril inferior
    enemy->y += LANE_DY;
    // Actualizamos el estado de los carriles
    m_laneStatus[lane] = 0;
    m_laneStatus[lane - 1] = 1;
}

void man_game_destroyEntity(Entity_t* entity)
{
    if (isA(entity, entityTypeShot)) {
        m_playerShot = 0;
    } else if (isA(entity, entityTypeEnemy)) {
        // Actualizamos la información de carriles
        u8 lane = m_man_game_getEnemyLane(entity);
        m_laneStatus[lane] = 0;
    }
    man_entity_markForDestruction(entity);
}

void man_game_playerShot(Entity_t* player)
{
    if (m_playerShot != 0) {
        return;
    }

    // Sólo podemos disparar si no hay otro disparo en curso
    {
        Entity_t *playerShot = m_man_game_createTemplateEntity(&playerShotTemplate);
        // El disparo sale centrado de la nave del jugador
        playerShot->x = player->x + ((player->width + playerShot->width) / 2); 
        m_playerShot = 1;
    }
}

/**
 * @precondition enemy es una entidad de tipo enemigo
 * @precondition shot es una entidad de tipo shot (player shot)
 */
void man_game_enemyHitByShot(Entity_t* enemy, Entity_t* shot)
{
    man_game_destroyEntity(enemy);
    man_game_destroyEntity(shot);

    // @TODO Actualizar marcador (cuando tengamos marcador)
}
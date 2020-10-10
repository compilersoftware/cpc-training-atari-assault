#include "ai.h"
#include <man/game.h>

/* Funciones privadas */

void m_sys_ai_updateSingleEntity(Entity_t* entity)
{
    entity->aiBehaviour(entity);
}


/* Funciones públicas */

void sys_ai_update()
{
    // Sólo queremos actualizar las entidades con IA
    man_entity_forAllMatching(m_sys_ai_updateSingleEntity, entityTypeAI);
}

void sys_ai_leftRightBehaviour(Entity_t* entity)
{
    const u8 rightBound = 80 - entity->width;
    if (entity->x == 0) {
        entity->vx = 1;
    } else if (entity->x == rightBound) {
        entity->vx = -1;
    }
}

void sys_ai_mothershipBehaviour(Entity_t* entity)
{
    // Intentamos crear un nuevo enemigo cuando estemos en la posición x=22
    // @TODO implementar un contador u otra lógica similar
    // @TODO Hemos cambiado la posición inicial para que no dé la casualidad de que los enemigos
    // recién creados bajen directamente al siguiente carril
    if (entity->x == 22) {
        man_game_createEnemy(entity);
    }

    sys_ai_leftRightBehaviour(entity);
}

void sys_ai_enemyBehaviour(Entity_t* entity)
{
    if ((entity->x & 0x07) == 0) {
        // Le pasamos la responsabilidad de bajar de carril al manager del juego, ya que es
        // quien conoce las reglas, las restricciones y el estado actual
        man_game_enemyLaneDown(entity);
    }
    sys_ai_leftRightBehaviour(entity);
}

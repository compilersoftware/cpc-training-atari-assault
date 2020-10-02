#include "ai.h"

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

void sys_ai_mothershipBehaviour(Entity_t* entity)
{
    const u8 rightBound = 80 - entity->width;
    if (entity->x == 0) {
        entity->vx = 1;
    } else if (entity->x == rightBound) {
        entity->vx = -1;
    }
}

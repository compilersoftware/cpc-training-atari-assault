#include "animations.h"
#include <man/entity.h>

/* Funciones privadas */

void m_sys_animations_updateSingleEntity(Entity_t* entity)
{
    if (-- (entity->animCounter) == 0) {
        ++ entity->frame;
        if (entity->frame->time == 0) {
            // Estamos en el último frame, volvemos al primero
            entity->frame = entity->frame->val.next;
        }
        // Cargamos el sprite de la animación
        entity->sprite = entity->frame->val.sprite;
        entity->animCounter = entity->frame->time;
    }
}

/* Funciones públicas */

void sys_animations_update()
{
    // Sólo queremos actualizar las entidades animadas
    man_entity_forAllMatching(m_sys_animations_updateSingleEntity, entityTypeAnimated);
}

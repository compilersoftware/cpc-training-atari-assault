#include "physics.h"
#include <man/entity.h>
#include <man/game.h>

/* Funciones privadas */

void m_sys_physics_checkKeyboard(Entity_t* entity)
{
    // En el vídeo se hace la prueba de trabajar aquí con una variable global vx
    // En este caso, curiosamente, no se consigue ninguna mejora en cuanto a longitud de código
    // generado

    cpct_scanKeyboard_f();

    // Movimiento izquierda/derecha
    entity->vx = 0;
    if (cpct_isKeyPressed(Key_O)) {
        entity->vx = -1;
    } else if (cpct_isKeyPressed(Key_P)) {
        entity->vx = 1;
    }

    // Disparo
    if (cpct_isKeyPressed(Key_Space)) {
        man_game_playerShot(entity);
    }
}

void m_sys_physics_updateSingleEntity(Entity_t* entity)
{
    // Por simplicidad, vamos a tratar aquí las entidades de tipo entityTypeControllable
    // @TODO llevar aparte esta funcionalidad
    if (entity->type & entityTypeControllable) {
        m_sys_physics_checkKeyboard(entity);
    }

    entity->x = entity->x + entity->vx;
    entity->y = entity->y + entity->vy;
}

/* Funciones públicas */

void sys_physics_update()
{
    // Sólo queremos actualizar las entidades movibles
    man_entity_forAllMatching(m_sys_physics_updateSingleEntity, entityTypeMovable);
}

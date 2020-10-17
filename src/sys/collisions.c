#include "collisions.h"
#include <man/entity.h>
#include <man/game.h>

/* Funciones privadas */

u8 m_sys_collisions_entitiesHaveCollided(Entity_t* entityLeft, Entity_t* entityRight)
{
    // @see https://gamedev.stackexchange.com/a/913/113499
    return !(
        (entityRight->x > (entityLeft->x + entityLeft->width))
        || ((entityRight->x + entityRight->width) < entityLeft->x)
        || (entityRight->y > (entityLeft->y + entityLeft->height))
        || ((entityRight->y + entityRight->height) < entityLeft->y)
        );
} 

void m_sys_collisions_updateEntities(Entity_t* entityLeft, Entity_t* entityRight)
{
    // 1. Ver si las dos entidades pueden colisionar

    // Hay que hacer la comprobación en los dos sentidos por la manera en la que 
    // recorre la lista de entidades
    u8 entity1CollidesEntity2 = entityLeft->collidesAgainstTypes & entityRight->type;
    u8 entity2CollidesEntity1 = entityRight->collidesAgainstTypes & entityLeft->type;

    if ((entity1CollidesEntity2 | entity2CollidesEntity1) == 0) {
        return;
    }

    // 2. Ver si las dos entidades han colisionado mirando los bounding boxes
    if (!m_sys_collisions_entitiesHaveCollided(entityLeft, entityRight)) {
        return;
    }

    // 3. Según los tipos que han colisionado, hay que decidir las acciones correspondientes
    if ((isA(entityLeft, entityTypeShot) 
        && isA(entityRight, entityTypeEnemy))
    ) {
        man_game_enemyHitByShot(entityRight, entityLeft);
        return;
    }
    if ((isA(entityRight, entityTypeShot) 
        && isA(entityLeft, entityTypeEnemy))
    ) {
        man_game_enemyHitByShot(entityLeft, entityRight);
        return;
    }
}

/* Funciones públicas */

void sys_collisions_update()
{
    // Sólo queremos actualizar las entidades que colisionan
    man_entity_forAllPairsMatchingComponent(m_sys_collisions_updateEntities, entityComponentCollision);
}

#include "collisions.h"
#include <man/entity.h>

/* Funciones privadas */

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

    // 3. Según los tipos que han colisionado, hay que decidir las acciones correspondientes
}

/* Funciones públicas */

void sys_collisions_update()
{
    // Sólo queremos actualizar las entidades que colisionan
    man_entity_forAllPairsMatchingComponent(m_sys_collisions_updateEntities, entityComponentCollision);
}

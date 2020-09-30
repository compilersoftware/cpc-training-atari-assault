#include "render.h"
#include <man/entity.h>
#include <sprites/mainPalette.h>

/* Atributos privados */


/* Funciones privadas */

void _sys_render_updateSingleEntity(Entity_t* entity)
{
    // Dibuja la actual (si no está marcada para destruir)
    // Draw current (if it is not marked for destruction)
    if (!(entity->type & entityTypeDead)) {
        u8* pVideoMem = cpct_getScreenPtr(CPCT_VMEM_START, entity->x, entity->y);
        cpct_drawSprite(entity->sprite, pVideoMem, entity->width, entity->height);
    }
}

/* Funciones públicas */

void sys_render_init()
{
    cpct_setVideoMode(0);
    cpct_setBorder(HW_BLACK);
    cpct_setPalette(mainPalette, sizeof(mainPalette));
}

void sys_render_update()
{
    man_entity_forAll(_sys_render_updateSingleEntity);
}
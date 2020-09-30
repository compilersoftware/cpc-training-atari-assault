#include "game.h"
#include "man/entity.h"
#include "sys/physics.h"
#include "sys/render.h"
#include "sprites/mothership.h"

/* Atributos privados */

const u8 sprite[] = {
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00
};

const Entity_t initEntity = {
    entityTypeMovable | entityTypeRenderable,   // type
    38, 10,                                     // x, y
    SPRITEMOTHERSHIP_W,  SPRITEMOTHERSHIP_H,    // width, height
    -1,  0,                                     // vx, vy
    spriteMothership                            // sprite
};


/* Funciones privadas */

void m_slowDown(u8 n)
{
    do {
        // cpct_waitHalts(), usada en los vídeos, no existe en CPCTelera
        // Implementamos un bucle vacío para ralentizar
        for (u16 i = 0; i < 500; i++) {
        }
        cpct_waitVSYNC();
    } while (n--);
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

    // Creamos una entidad
    entity = man_entity_create();
    cpct_memcpy(entity, &initEntity, sizeof(Entity_t));

}

void man_game_play()
{
    while(1) {

        // Actualizar sistemas
        sys_physics_update();
        sys_render_update();

        // Actualizar manager
        man_entity_update();

        cpct_waitVSYNC;
    }
}

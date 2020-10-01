#include "game.h"
#include "man/entity.h"
#include "sys/physics.h"
#include "sys/render.h"
#include "sys/ai.h"
#include "sprites/mothership.h"
#include "sprites/playership.h"

/* Atributos privados */

const u8 sprite[] = {
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0x00
};

const Entity_t mothershipTemplate = {
    entityTypeMovable | entityTypeRenderable | entityTypeAI,    // type
    38, 10,                                                     // x, y
    SPRITEMOTHERSHIP_W,  SPRITEMOTHERSHIP_H,                    // width, height
    -1,  0,                                                     // vx, vy
    spriteMothership                                            // sprite
};

const Entity_t scoreboardPlayerTemplate = {
    entityTypeRenderable,                        // type
    0, 192,                                     // x, y
    SPRITEPLAYESHIP_1_W,  SPRITEPLAYESHIP_1_H,  // width, height
    0,  0,                                      // vx, vy
    spritePlayeship_1                           // sprite
};

const Entity_t playerTemplate = {
    entityTypeMovable | entityTypeRenderable | entityTypeControllable,  // type
    38, 180,                                                            // x, y
    SPRITEPLAYESHIP_0_W,  SPRITEPLAYESHIP_0_H,                          // width, height
    0,  0,                                                              // vx, vy
    spritePlayeship_0                                                   // sprite
};


/* Funciones privadas */

void m_man_game_slowDown(u8 n)
{
    cpct_waitHalts(n);
    cpct_waitVSYNC();
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
}

void man_game_play()
{
    while(1) {

        // Actualizar sistemas
        sys_ai_update();
        sys_physics_update();
        sys_render_update();

        // Actualizar manager
        man_entity_update();

        m_man_game_slowDown(4);
        cpct_waitVSYNC;
    }
}

#pragma once
#include <cpctelera.h>


/* Constantes */

// Tipos de entidades (en formato mapa de bits)
#define entityTypeInvalid 0x00      // Inválida
#define entityTypeRenderable 0x01   // Dibujable
#define entityTypeMovable 0x02      // Movible
#define entityTypeControllable 0x04 // Controlable por el jugador
#define entityTypeAI 0x08           // Controlable por la IA
#define entityTypeDead 0x80 
#define entityTypeDefault 0x7F

#define MAX_ENTITIES 12

/* Estructuras de datos */

typedef struct te {
    u8 type;
    u8 x, y;
    u8 width, height;
    i8 vx, vy;
    u8* sprite;
} Entity_t;

/* Interfaz pública */

void man_entity_init();
Entity_t* man_entity_create();
void man_entity_markForDestruction(Entity_t* entity);
void man_entity_forAll(void (*fnPtr)(Entity_t*));
void man_entity_forAllMatching(void (*fnPtr)(Entity_t*), u8 signature);
void man_entity_update();
u8 man_entity_freeSpace();

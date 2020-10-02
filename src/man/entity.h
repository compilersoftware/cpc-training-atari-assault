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

// Necesitamos hacer una declaración adelantada (forward declaration), porque dentro de algún campo
// vamos a hacer referencia al propio tipo
typedef struct Ent_t Entity_t; // El tipo se llama Ent_t y tiene como alias Entity_t

// Definimos tipos de punteros a función y sus respectivos alias
typedef void (*BehaviourFunc_t)(Entity_t *); // En este caso, PtrFunc_t es el alias
typedef void (*UpdateFunc_t)(Entity_t *); // En este caso, PtrFunc_t es el alias

typedef struct Ent_t {
    u8 type;
    u8 x, y;
    u8 width, height;
    i8 vx, vy;
    u8* sprite;
    BehaviourFunc_t aiBehaviour; // Puntero a la función que implementa el comportamiento (IA)
};

/* Interfaz pública */

void man_entity_init();
Entity_t* man_entity_create();
void man_entity_markForDestruction(Entity_t* entity);
void man_entity_forAll(UpdateFunc_t updateFunctionPtr);
void man_entity_forAllMatching(UpdateFunc_t updateFunctionPtr, u8 signature);
void man_entity_update();
u8 man_entity_freeSpace();

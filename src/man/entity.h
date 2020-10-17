#pragma once
#include <cpctelera.h>

/* Constantes */

// Tipos de entidades (en formato mapa de bits)
#define entityTypeInvalid 0x00
#define entityTypePlayer 0x01
#define entityTypeEnemy 0x02
#define entityTypeMothership 0x04
#define entityTypeShot 0x08
#define entityTypeDead 0x80
#define entityTypeDefault entityTypeEnemy 

// Componentes (en formato mapa de bits)
#define entityComponentRender 0x01
#define entityComponentMovement 0x02
#define entityComponentInput 0x04
#define entityComponentAi 0x08
#define entityComponentAnimation 0x10
#define entityComponentCollision 0x20
#define entityComponentDefault 0x00

#define MAX_ENTITIES 12

// Definimos algunas macros para mejorar la legibilidad del código
#define isValid(E) ((E)->type != entityTypeInvalid)
#define isDead(E) ((E)->type & entityTypeDead)
#define signatureMatches(E, S) (((E)->components & S) == S)
#define isA(E, T) ((E)->type & T)

/* Estructuras de datos */

// Necesitamos hacer una declaración adelantada (forward declaration), porque dentro de algún campo
// vamos a hacer referencia al propio tipo
typedef struct Entity_t Entity_t; // El tipo se llama Entity_t y tiene como alias Entity_t
typedef struct AnimFrame_t AnimFrame_t;
typedef union SpriteOrNextFrame_t SpriteOrNextFrame_t;

// Definimos tipos de punteros a función y sus respectivos alias
typedef void (*BehaviourFunc_t)(Entity_t *); // En este caso, BehaviourFunc_t es el alias
typedef void (*UpdateFunc_t)(Entity_t *); // En este caso, UpdateFunc_t es el alias
typedef void (*UpdatePairFunc_t)(Entity_t *, Entity_t*); // En este caso, UpdatePairFunc_t es el alias

// Entidad
typedef struct Entity_t {
    u8 type;
    u8 components; // Mapa de bits que indica los componentes que tiene la entidad
    u8 x, y;
    u8 width, height;
    i8 vx, vy;
    u8 const * sprite;
    BehaviourFunc_t aiBehaviour; // Puntero a la función que implementa el comportamiento (IA)
    u8 aiCounter; // Contador de frames de IA
    AnimFrame_t const * frame; // Puntero al frame de animación actual
    u8 animCounter; // Contador de frames de animación
    u8 collidesAgainstTypes; // Types contra los que colisiona la entidad
};

// Animación
union SpriteOrNextFrame_t {
    u8 const * const sprite;
    AnimFrame_t const * const next;
};

struct AnimFrame_t {
    u8 const time; // Lo definimos como constante porque no queremos que nadie lo cambie por error
    SpriteOrNextFrame_t val; // Si time == 0, val apunta al primer fotograma. Si no, es el sprite de esa animación
};

/* Interfaz pública */

void man_entity_init();
Entity_t* man_entity_create();
Entity_t* man_entity_clone(Entity_t* entity);
void man_entity_markForDestruction(Entity_t* entity);
void man_entity_forAll(UpdateFunc_t updateFunctionPtr);
void man_entity_forAllMatchingComponent(UpdateFunc_t updateFunctionPtr, u8 signature);
void man_entity_forAllPairsMatchingComponent(UpdatePairFunc_t updateFunctionPtr, u8 signature);
void man_entity_update();
u8 man_entity_freeSpace();

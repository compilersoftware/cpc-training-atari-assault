#pragma once
#include <cpctelera.h>
#include <man/entity.h>


/* Constantes */


/* Estructuras de datos */


/* Interfaz pública */

void man_game_init();
void man_game_play();
void man_game_createEnemy(Entity_t* mothership);
void man_game_enemyLaneDown(Entity_t* enemy);
void man_game_destroyEntity(Entity_t* entity);
void man_game_playerShot(Entity_t* player);

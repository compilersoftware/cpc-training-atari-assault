#pragma once
#include <cpctelera.h>
#include <man/entity.h>

/* Interfaz pública */

void sys_ai_update();
void sys_ai_leftRightBehaviour(Entity_t *entity);
void sys_ai_mothershipBehaviour(Entity_t *entity);

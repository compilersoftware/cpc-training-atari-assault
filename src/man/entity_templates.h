#pragma once

#include <man/entity.h>

// Carriles enemigos

#define LANE_DY 30
#define LANE_2_Y 40
#define LANE_1_Y (LANE_2_Y + LANE_DY)
#define LANE_0_Y (LANE_1_Y + LANE_DY)

// Plantillas de entidades

extern const Entity_t mothershipTemplate;
extern const Entity_t enemy1Template;
extern const Entity_t scoreboardPlayerTemplate;
extern const Entity_t playerTemplate;

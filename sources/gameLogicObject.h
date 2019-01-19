#pragma once
#include "map.h"

#define TILESIZE 25

class GameLogicObject {
public:
    Map *gameMap;
    GameLogicObject(Map* map) { this->gameMap = map; };
};
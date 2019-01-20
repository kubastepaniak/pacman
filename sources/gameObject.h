#pragma once
#include <QGraphicsObject>
#include "map.h"

#define TILESIZE 25

class GameObject : public QGraphicsObject {
    Q_OBJECT
public:
    Map *gameMap;
    GameObject(Map* map = nullptr) { this->gameMap = map; }
};
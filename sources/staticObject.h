#pragma once
#include "gameObject.h"

class StaticObject : public GameObject {
    Q_OBJECT
public:
    const int xID;
    const int yID;
    StaticObject(int x, int y, Map* map = nullptr) : GameObject(map), xID(x), yID(y) { };
};
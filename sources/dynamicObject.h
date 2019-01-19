#pragma once
#include "gameObject.h"

class DynamicObject : public GameObject {
    Q_OBJECT
protected:
    int xPos;
    int yPos;
    virtual bool moveUpPossible() = 0;
    virtual bool moveDownPossible() = 0;
    virtual bool moveLeftPossible() = 0;
    virtual bool moveRightPossible() = 0;
public:
/*     int xPos;
    int yPos; */
    DynamicObject(int x, int y, Map *map = nullptr) :  GameObject(map), xPos(x), yPos(y) { }
};
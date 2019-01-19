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
    virtual void move(int direction) = 0;
    enum Direction { none = 0, right = Qt::Key_Right, left = Qt::Key_Left, up = Qt::Key_Up, down = Qt::Key_Down};
public:
    DynamicObject(int x, int y, Map *map = nullptr) :  GameObject(map), xPos(x), yPos(y) { }
};
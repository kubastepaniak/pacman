#include "dynamicObject.h"

DynamicObject::DynamicObject(int x, int y, Map *map) 
    : GameObject(map), xPos(x), yPos(y),
      xCoordinate(x * TILESIZE),
      yCoordinate(y * TILESIZE) { }

bool DynamicObject::moveInDirectionPossible(int direction) {
    if (direction == Direction::left) {
        if (moveLeftPossible())
            return true;
    } else if (direction == Direction::right) {
        if (moveRightPossible())
            return true;
    } else if (direction == Direction::up) {
        if (moveUpPossible())
            return true;
    } else if (direction == Direction::down) {
        if (moveDownPossible())
            return true;
    }
    return false;
}

QRectF DynamicObject::boundingRect() const {
    return QRectF(xCoordinate, yCoordinate, TILESIZE, TILESIZE);
}

void DynamicObject::updateCoords() {
    xCoordinate = xPos * TILESIZE;
    yCoordinate = yPos * TILESIZE;
}
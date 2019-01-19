#include "ghost.h"

Ghost::Ghost(int x, int y, Map *map)
    : DynamicObject(x, y, map),
      xCoordinate(x * TILESIZE),
      yCoordinate(y * TILESIZE) { }

bool Ghost::moveUpPossible() {
    if ((*gameMap)(xPos, yPos - 1) != MapTag::wall)
        return true;
    else
        return false;
}

bool Ghost::moveDownPossible() {
    if ((*gameMap)(xPos, yPos + 1) != MapTag::wall)
        return true;
    else
        return false;
}

bool Ghost::moveRightPossible() {
    if ((*gameMap)(xPos + 1, yPos) != MapTag::wall)
        return true;
    else
        return false;
}

bool Ghost::moveLeftPossible() {
    if ((*gameMap)(xPos - 1, yPos) != MapTag::wall)
        return true;
    else
        return false;
}
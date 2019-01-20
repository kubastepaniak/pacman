#include "ghost.h"

Ghost::Ghost(int x, int y, Map *map, Player *target)
    : DynamicObject(x, y, map),
      xCoordinate(x * TILESIZE),
      yCoordinate(y * TILESIZE) {
    player = target;
}

bool Ghost::moveUpPossible() {
    if ((*gameMap)(xPos, yPos - 1) != MapTag::wall && 
        ((*gameMap)(xPos, yPos - 1) != MapTag::gate || state == State::init))
        return true;
    else
        return false;
}

bool Ghost::moveDownPossible() {
    if ((*gameMap)(xPos, yPos + 1) != MapTag::wall && 
        ((*gameMap)(xPos, yPos - 1) != MapTag::gate || state == State::init))
        return true;
    else
        return false;
}

bool Ghost::moveRightPossible() {
    if ((*gameMap)(xPos + 1, yPos) != MapTag::wall && 
        ((*gameMap)(xPos, yPos - 1) != MapTag::gate || state == State::init))
        return true;
    else
        return false;
}

bool Ghost::moveLeftPossible() {
    if ((*gameMap)(xPos - 1, yPos) != MapTag::wall && 
        ((*gameMap)(xPos, yPos - 1) != MapTag::gate || state == State::init))
        return true;
    else
        return false;
}
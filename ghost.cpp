#include "ghost.h"

Ghost::Ghost(int x, int y, Map *map, Player *target)
    : DynamicObject(x, y, map) {
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

void Ghost::updateDirection(int direction) {
    switch(direction) {
        case Direction::right: {
            if((*gameMap)(xPos, yPos) == MapTag::teleport &&
               xPos != TP_LEFT_X) {
                xPos = TP_LEFT_X;
            } else {
                xPos++;
            }
            break;
        }
        case Direction::left: {
            if((*gameMap)(xPos, yPos) == MapTag::teleport &&
               xPos != TP_RIGHT_X) {
                xPos = TP_RIGHT_X;
            } else {
                xPos--;
            }
            break;
        }
        case Direction::up: {
            yPos--;
            break;
        }
        case Direction::down: {
            yPos++;
            break;
        }
        default: break;
    }
}

void Ghost::move(int direction) {
    if(player->xPos == this->xPos && player->yPos == this->yPos)
        emit playerCaught();

    if(moveInDirectionPossible(direction))
        updateDirection(direction);

    prepareGeometryChange();
    updateCoords();
}

void Ghost::changeState() {
    if(state == State::init) {
        //queuedDirection = Direction::right; // no clue why is this here
        state = State::chase;
    } else if(state == State::chase) {
        state = State::avoid;
    } else {
        state = State::chase;
    }
}
#include "redGhost.h"
#include <iostream>

RedGhost::RedGhost(Map *map, Player *target)
    : Ghost(default_x, default_y, map, target) {
    state = State::init;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
}

void RedGhost::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawPixmap(xCoordinate, yCoordinate, QPixmap(QString("sources/red.png")));
}

QRectF RedGhost::boundingRect() const {
    return QRectF(xCoordinate, yCoordinate, TILESIZE, TILESIZE);
}

void RedGhost::move(int direction) {
    if(moveInDirectionPossible(direction))
        updateDirection(direction);

    prepareGeometryChange();
    updateCoords();
}

void RedGhost::updateCoords() {
    xCoordinate = xPos * TILESIZE;
    yCoordinate = yPos * TILESIZE;
}
// functions in between could be methods of dynamic object
void RedGhost::updateDirection(int direction) {
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

void RedGhost::updatePosition() {
    switch(state) {
        case State::init: {
            move(currentDirection);
            break;
        }
        case State::chase: case State::avoid: {
            goWhere();
            if(moveInDirectionPossible(queuedDirection))
                currentDirection = queuedDirection;
            move(currentDirection);
            break;
        }
    }
}

void RedGhost::goWhere() {
    int targetX = player->xPos;
    int targetY = player->yPos;
    
    if(state == State::avoid) { // run away mode
        if(targetX > xPos) { // pacman is on the right of the ghost
            if(moveLeftPossible()) { // run left
                queuedDirection = Direction::left;
            } else if (targetY > yPos) { // cant go left then run up if possible
                if(moveUpPossible())
                    queuedDirection = Direction::up;
            } else if (targetY < yPos) { // or down
                if(moveDownPossible())
                    queuedDirection = Direction::down;
            }
        } else if(targetX < xPos) { // pacman is on the left of the ghost
            if(moveRightPossible()) { // run right
                queuedDirection = Direction::right;
            } else if (targetY > yPos) { // cant go right then run up if possible
                if(moveUpPossible())
                    queuedDirection = Direction::up;
            } else if (targetY < yPos) { // or down
                if(moveDownPossible())
                    queuedDirection = Direction::down;
            }
        } else {
            if(targetY > yPos) { // pacman is below
                if(moveUpPossible()) // run up
                    queuedDirection = Direction::up;
            } else if(targetY < yPos) { // pacman is above
                if(moveDownPossible())// run down
                    queuedDirection = Direction::down;
            } else {
                emit playerCaught();
            }
        }
    } else {
        if(targetX > xPos) { // pacman is on the right of the ghost
            if(moveRightPossible()) {
                queuedDirection = Direction::right;
            } else if (targetY > yPos) { // cant go right then go down if possible
                if(moveDownPossible()) 
                    queuedDirection = Direction::down;
            } else if (targetY < yPos) { // or up
                if(moveUpPossible())
                    queuedDirection = Direction::up;
            }
        } else if(targetX < xPos) { // pacman is on the left of the ghost
            if(moveLeftPossible()) {
                queuedDirection = Direction::left;
            } else if (targetY > yPos) { // cant go left then go down if possible
                if(moveDownPossible())
                    queuedDirection = Direction::down;
            } else if (targetY < yPos) { // or up
                if(moveUpPossible())
                    queuedDirection = Direction::up;
            }
        } else {
            if(targetY > yPos) { // pacman is below
                if(moveDownPossible())
                    queuedDirection = Direction::down;
            } else if(targetY < yPos) { // pacman is above
                if(moveUpPossible())
                    queuedDirection = Direction::up;
            } else {
                emit playerCaught();
            }
        }
    }
}

void RedGhost::go() {
    currentDirection = Direction::up;
    timer->start(STEP_RATE);
}

void RedGhost::changeState() {
    if(state == State::init) {
        queuedDirection = Direction::right;
        state = State::chase;
    } else if(state == State::chase) {
        state = State::avoid;
    } else {
        state = State::chase;
    }
}
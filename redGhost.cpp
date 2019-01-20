#include "redGhost.h"
#include <iostream>

RedGhost::RedGhost(Map *map)
    : Ghost(default_x, default_y, map) {
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

void RedGhost::updatePosition(int direction) {
    switch(state) {
        case State::init: {
            move(currentDirection);
            break;
        }
        case State::chase: {
            if(moveInDirectionPossible(queuedDirection))
                currentDirection = queuedDirection;
            move(currentDirection);
            break;
        }
    }
}

void RedGhost::startup() { 
    int moves[3] = { Direction::up };
    for(int step : moves) {
        currentDirection = step;
    }
}

void RedGhost::go() {
    //startup();
    currentDirection = Direction::up;
    timer->start(STEP_RATE);
}
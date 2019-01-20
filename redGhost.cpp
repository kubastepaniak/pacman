#include "redGhost.h"

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

void RedGhost::updatePosition() {
    switch(state) {
        case State::init: {
            //move(currentDirection);
            move(Direction::up);
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
                reset();
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
            }
        }
    }
}

void RedGhost::reset() {
    state = State::init;
    currentDirection = Direction::up;
    xPos = default_x;
    yPos = default_y;
}
/* 
void RedGhost::go() {
    currentDirection = Direction::up;
    timer->start(STEP_RATE);
} */
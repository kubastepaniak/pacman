#include "greenGhost.h"
#include <cstdlib>
#include <iostream>

GreenGhost::GreenGhost(Map *map, Player *target)
    : Ghost(default_x, default_y, map, target) {
    std::srand(time(NULL));
    state = State::init;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePosition()));

    QTimer *randomizer = new QTimer(this);
    connect(randomizer, SIGNAL(timeout()), this, SLOT(randomizeTarget()));
    randomizer->start(2000);
    targetX = 1;
    targetY = 2;
}

void GreenGhost::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawPixmap(xCoordinate, yCoordinate, QPixmap(QString("sources/green.png")));
}

void GreenGhost::updatePosition() {
    switch(state) {
        case State::init: {
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

void GreenGhost::reset() {
    state = State::init;
    xPos = default_x;
    yPos = default_y;
}

void GreenGhost::goWhere() {  
    if(targetY > yPos) {
        if(moveDownPossible()) {
            queuedDirection = Direction::down;
        } else if (targetX > xPos) {
            if(moveRightPossible()) 
                queuedDirection = Direction::right;
        } else if (targetX < xPos) {
            if(moveLeftPossible())
                queuedDirection = Direction::left;
        }
    } else if(targetY < yPos) {
        if(moveUpPossible()) {
            queuedDirection = Direction::up;
        } else if (targetX > xPos) {
            if(moveRightPossible())
                queuedDirection = Direction::right;
        } else if (targetX < xPos) {
            if(moveLeftPossible())
                queuedDirection = Direction::left;
        }
    } else {
        if(targetX > xPos) {
            if(moveRightPossible())
                queuedDirection = Direction::right;
        } else if(targetX < xPos) {
            if(moveLeftPossible())
                queuedDirection = Direction::left;
        }
    }
}

void GreenGhost::randomizeTarget() {
    int roll = std::rand() % POINTS;
    while(targetX == targets[roll][0] && targetY == targets[roll][1])
        roll = std::rand() % POINTS;

    targetX = targets[roll][0];
    targetY = targets[roll][1];
    std::cout << targetX << " " << targetY << "\n";
}
#include "greenGhost.h"

GreenGhost::GreenGhost(Map *map, Player *target)
    : Ghost(default_x, default_y, map, target) {
    state = State::init;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
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

void GreenGhost::goWhere() { }

void GreenGhost::reset() {
    state = State::init;
    //currentDirection = Direction::up;
    xPos = default_x;
    yPos = default_y;
}
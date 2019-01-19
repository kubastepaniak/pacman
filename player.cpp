#include "player.h"
#include <iostream>

Player::Player(Map *cMap, Map *map)
    : DynamicObject(DEFAULT_X, DEFAULT_Y, map),
      xCoordinate(DEFAULT_X * TILESIZE),
      yCoordinate(DEFAULT_Y * TILESIZE) { 
    collectablesMap = cMap;
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    currentDirection = Direction::none;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
    timer->start(200); 
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::yellow);
    painter->drawPie(xCoordinate, yCoordinate, TILESIZE, TILESIZE,
                     16 * (angle / 2) + startAngle, 16 * (360 - angle));
}

QRectF Player::boundingRect() const {
    return QRectF(xCoordinate, yCoordinate, TILESIZE, TILESIZE);
}

void Player::updatePosition() {
    if(moveInDirectionPossible(queuedDirection))
        currentDirection = queuedDirection;
    move(currentDirection);
}

bool Player::moveUpPossible() {
    if ((*gameMap)(xPos, yPos - 1) != MapTag::wall && 
        (*gameMap)(xPos, yPos - 1) != MapTag::gate)
        return true;
    else
        return false;
}

bool Player::moveDownPossible() {
    if ((*gameMap)(xPos, yPos + 1) != MapTag::wall && 
        (*gameMap)(xPos, yPos + 1) != MapTag::gate)
        return true;
    else
        return false;
}

bool Player::moveRightPossible() {
    if ((*gameMap)(xPos + 1, yPos) != MapTag::wall && 
        (*gameMap)(xPos + 1, yPos) != MapTag::gate)
        return true;
    else
        return false;
}

bool Player::moveLeftPossible() {
    if ((*gameMap)(xPos - 1, yPos) != MapTag::wall && 
        (*gameMap)(xPos - 1, yPos) != MapTag::gate)
        return true;
    else
        return false;
}

void Player::updateDirection(int direction) {
    switch(direction) {
        case Direction::right: {
            if((*gameMap)(xPos, yPos) == MapTag::teleport &&
               xPos != TP_LEFT_X) {
                xPos = TP_LEFT_X;
            } else {
                xPos++;
            }
            startAngle = DirectAngle::right;
            break;
        }
        case Direction::left: {
            if((*gameMap)(xPos, yPos) == MapTag::teleport &&
               xPos != TP_RIGHT_X) {
                xPos = TP_RIGHT_X;
            } else {
                xPos--;
            }
            startAngle = DirectAngle::left;
            break;
        }
        case Direction::up: {
            yPos--;
            startAngle = DirectAngle::up;
            break;
        }
        case Direction::down: {
            yPos++;
            startAngle = DirectAngle::down;
            break;
        }
        default: break;
    }
}

void Player::keyPressEvent(QKeyEvent * event) {
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_Down  || event->key() == Qt::Key_Up) {
        if(currentDirection == Direction::none)
            currentDirection = event->key();
        else
            queuedDirection = event->key();
    }
}

void Player::move(int direction) {
    if(moveInDirectionPossible(direction))
        updateDirection(direction);

    prepareGeometryChange();
    updateCoords();
    checkCollectable();
}

void Player::checkCollectable() {
    if((*collectablesMap)(xPos, yPos) == CollTag::point) {
        (*collectablesMap)(xPos, yPos) = 0;
        emit itemCollected(CollTag::point);
    } else if((*collectablesMap)(xPos, yPos) == CollTag::candy) {
        (*collectablesMap)(xPos, yPos) = 0;
        emit itemCollected(CollTag::candy);
    }
}

void Player::updateCoords() {
    xCoordinate = xPos * TILESIZE;
    yCoordinate = yPos * TILESIZE;
}
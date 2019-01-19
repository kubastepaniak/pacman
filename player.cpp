#include "player.h"
#include <iostream>

Player::Player(Map *cMap, Map *map)
    : DynamicObject(DEFAULT_X, DEFAULT_Y, map),
      xCoordinate(DEFAULT_X * TILESIZE),
      yCoordinate(DEFAULT_Y * TILESIZE) { 
    collectablesMap = cMap;
    this->setFlag(QGraphicsItem::ItemIsFocusable);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::yellow);
    std::cout << "here ffs\n";
    painter->drawPie(xPos * TILESIZE, yPos * TILESIZE, TILESIZE, TILESIZE,
                     16 * (angle / 2) + startAngle, 16 * (360 - angle));
    /* painter->drawPie(xCoordinate, yCoordinate, TILESIZE, TILESIZE,
                     16 * (angle / 2) + startAngle, 16 * (360 - angle)); */
}

QRectF Player::boundingRect() const {
    //return QRectF(xCoordinate, yCoordinate, TILESIZE, TILESIZE);
    return QRectF(xPos * TILESIZE, yPos * TILESIZE, TILESIZE, TILESIZE);
    //return QRectF(pos().x(), pos().y(), TILESIZE, TILESIZE);
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
    if(direction) {
        switch(direction) {
            case Qt::Key_Right: {
                xPos++;
                startAngle = DirectAngle::right;
                break;
            }
            case Qt::Key_Left: {
                xPos--;
                startAngle = DirectAngle::left;
                break;
            }
            case Qt::Key_Up: {
                yPos--;
                startAngle = DirectAngle::up;
                break;
            }
            case Qt::Key_Down: {
                yPos++;
                startAngle = DirectAngle::down;
                break;
            }
        }
    }
}

void Player::keyPressEvent(QKeyEvent * event) {
    if (event->key() == Qt::Key_Left) {
        if (moveLeftPossible()) {
            //setPos(x() - TILESIZE, y());
            xPos--;
            //updateDirection(Qt::Key_Left);
            //this->setStartAngle(16 * (angle / 2) + (180 * 16));
        }
	} else if (event->key() == Qt::Key_Right) {
        if (moveRightPossible()) {
            setPos(x() + TILESIZE, y());
            xPos++;
        }
	} else if (event->key() == Qt::Key_Up) {
        if (moveUpPossible()) {
            //setPos(x(), y() - TILESIZE);
            yPos--;
        }
	} else if (event->key() == Qt::Key_Down) {
        if (moveDownPossible()) {
            //setPos(x(), y() + TILESIZE);
            yPos++;
        }
	}
    updateCoords();
    //checkCollectable();
}

void Player::checkCollectable() {
    if((*collectablesMap)(xPos, yPos) == CollTag::point) {
        (*collectablesMap)(xPos, yPos) = 0;
        emit itemCollected(1);
    } else if((*collectablesMap)(xPos, yPos) == CollTag::candy) {
        (*collectablesMap)(xPos, yPos) = 0;
        emit itemCollected(3);
    }
}

void Player::updateCoords() {
    xCoordinate = xPos * TILESIZE;
    yCoordinate = yPos * TILESIZE;
}
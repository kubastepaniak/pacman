#include "player.h"

Player::Player(Map *cMap, Map *map)
    : DynamicObject(DEFAULT_X, DEFAULT_Y, map),
      xCoordinate(DEFAULT_X * TILESIZE),
      yCoordinate(DEFAULT_Y * TILESIZE) { 
    collectablesMap = cMap;
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    currentDirection = Direction::none;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
    timer->start(STEP_RATE); 
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    if(isBuffed)
        painter->setBrush(Qt::red);
    else
        painter->setBrush(Qt::yellow);
    painter->setPen(Qt::NoPen);
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
        if(currentDirection == Direction::none) {
            emit start();
            currentDirection = event->key();
        }
        else
            queuedDirection = event->key();
    }
}

void Player::move(int direction) {
    static int counter = 0;
    if(moveInDirectionPossible(direction))
        updateDirection(direction);

    prepareGeometryChange();
    updateCoords();
    checkCollectable();
    
    if(direction || counter == 0) {
        counter++;
        if(counter == 5) {
            emit changeGhostState();
            //counter = 0;
        }
    }
}

void Player::checkCollectable() {
    if((*collectablesMap)(xPos, yPos) == CollTag::point) {
        (*collectablesMap)(xPos, yPos) = 0;
        emit itemCollected(CollTag::point);
    } else if((*collectablesMap)(xPos, yPos) == CollTag::candy) {
        (*collectablesMap)(xPos, yPos) = 0;
        emit itemCollected(CollTag::candy);
        buffUp();
    }
}

void Player::buffUp() {
    isBuffed = true;
    emit changeGhostState();

    QTimer *buffEnd = new QTimer(this);
    connect(buffEnd, SIGNAL(timeout()), this, SLOT(buffFading()));
    buffEnd->setSingleShot(true);
    
    QTimer *chaseStart = new QTimer(this);
    connect(chaseStart, SIGNAL(timeout()), this, SLOT(buffFading()));
    chaseStart->setSingleShot(true);
    
    buffEnd->start(5 * STEP_RATE * 5);
    chaseStart->start(5 * STEP_RATE * 6);
}

void Player::buffFading() {
    if(isBuffed) {
        isBuffed = false;
    } else {
        emit changeGhostState();
    }
}

void Player::updateCoords() {
    xCoordinate = xPos * TILESIZE;
    yCoordinate = yPos * TILESIZE;
}
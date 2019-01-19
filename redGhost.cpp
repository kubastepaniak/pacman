#include "redGhost.h"

RedGhost::RedGhost(Map *map)
    : Ghost(13, 15, map) { }

void RedGhost::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawPixmap(xCoordinate, yCoordinate, QPixmap(QString("sources/red.png")));
}

QRectF RedGhost::boundingRect() const {
    return QRectF(xCoordinate, yCoordinate, TILESIZE, TILESIZE);
}

void RedGhost::move(int direction) { }
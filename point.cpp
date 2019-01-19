#include "point.h"
#include <iostream>

Point::Point(int xindex, int yindex, int type)
    : Collectable(xindex, yindex, type),
      xCoordinate(xindex * bgSize),
      yCoordinate(yindex * bgSize) { }

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(xCoordinate + offset, yCoordinate + offset, radius, radius);
}

QRectF Point::boundingRect() const {
    return QRectF(xCoordinate, yCoordinate, TILESIZE, TILESIZE);
}
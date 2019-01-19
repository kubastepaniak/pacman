#include "point.h"
#include <iostream>

Point::Point(int xindex, int yindex, int type)
    : Collectable(xindex, yindex, type),
      xCoordinate(xindex * bgSize + offset),
      yCoordinate(yindex * bgSize + offset) { }

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(Qt::yellow);
    painter->fillRect(this->boundingRect(), Qt::red);
    //painter->drawEllipse(xCoordinate + offset, yCoordinate + offset, radius, radius);
}

QRectF Point::boundingRect() const {
    return QRectF(xCoordinate, yCoordinate, radius, radius);
}
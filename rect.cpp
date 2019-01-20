#include "rect.h"

Rect::Rect(int xindex, int yindex, Map *map)
    : StaticObject(xindex, yindex, map),
      xCoordinate(xindex * tileSize),
      yCoordinate(yindex * tileSize) {
    switch((*map)(xindex, yindex)) {
        case MapTag::space:     fill = Qt::black;       break;
        case MapTag::wall:      fill = Qt::blue;        break;
        case MapTag::gate:      fill = Qt::darkBlue;    break;
        case MapTag::teleport:  fill = Qt::black;  break;
        default:                fill = Qt::green;       break;
    }
}

void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->fillRect(xCoordinate, yCoordinate, tileSize, tileSize, fill);
}

QRectF Rect::boundingRect() const {
    return QRectF(xCoordinate, yCoordinate, tileSize, tileSize);
}
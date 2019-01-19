#pragma once
#include "sources/staticObject.h"
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

class Rect : public StaticObject {
    Q_OBJECT
private:
    int xCoordinate;
    int yCoordinate;
    const static int tileSize = TILESIZE;
    QColor fill;
public:
    Rect(int xindex, int yindex, Map *map = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};
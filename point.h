#pragma once
#include "sources/collectable.h"
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

class Point : public Collectable {
    Q_OBJECT
private:
    int xCoordinate;
    int yCoordinate;
    const static int offset = 10;
    const static int radius = 5;
public:
    Point(int xindex, int yindex, int type);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};
#pragma once
#include "sources/collectable.h"
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

class Candy : public Collectable {
    Q_OBJECT
private:
    int xCoordinate;
    int yCoordinate;
    const static int offset = 6;
    const static int radius = 13;
public:
    Candy(int xindex, int yindex, int type);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};
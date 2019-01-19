#pragma once
#include "ghost.h"
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

class RedGhost : public Ghost {
    Q_OBJECT

protected:
    void move(int direction) override;

private:
    int currentDirection;
    int queuedDirection;

public:
    RedGhost(Map *map);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};
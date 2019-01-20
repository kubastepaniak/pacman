#pragma once
#include "ghost.h"
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

class GreenGhost : public Ghost {
    Q_OBJECT

protected:
    void goWhere() override;

private:
    static const int default_x = 13;
    static const int default_y = 15;
    void updateDirection(int direction);
    void reset();

public:
    GreenGhost(Map *map, Player *target);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void updatePosition();
};
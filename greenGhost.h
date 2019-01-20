#pragma once
#include "ghost.h"
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

#define POINTS 6

class GreenGhost : public Ghost {
    Q_OBJECT

protected:
    void goWhere() override;

private:
    static const int default_x = 13;
    static const int default_y = 15;
    int targetX;
    int targetY;
    void updateDirection(int direction);
    void reset();

    const int targets[POINTS][2] = {{1, 2},  {26, 2},
                               {9, 15}, {18, 15},
                               {1, 30}, {26, 30}};

public:
    GreenGhost(Map *map, Player *target);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void updatePosition();
    void randomizeTarget();
};
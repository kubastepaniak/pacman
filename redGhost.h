#pragma once
#include "ghost.h"
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

/*
    Red ghost's behaviour is pretty boring and he can
    get stuck atm. It just simply moves right or left if
    pacman is to the side and then up or down if he's
    below or above.
*/

class RedGhost : public Ghost {
    Q_OBJECT

protected:
    void goWhere() override;

private:
    static const int default_x = 14;
    static const int default_y = 15;
    void updateDirection(int direction);
    void reset();

public:
    RedGhost(Map *map, Player *target);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void go();
    void updatePosition();
};
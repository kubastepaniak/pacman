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
    void move(int direction) override;

private:
    static const int default_x = 14;
    static const int default_y = 15;
    int currentDirection;
    int queuedDirection;
    void updateDirection(int direction);
    void updateCoords();
    void goWhere();
    void reset();

public:
    RedGhost(Map *map, Player *target);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

public slots:
    void go();
    void changeState();
    void updatePosition();
};
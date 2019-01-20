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
    const int default_x = 13;
    const int default_y = 15;
    int currentDirection;
    int queuedDirection;
    void updateDirection(int direction);
    void updateCoords();

    void startup();

public:
    RedGhost(Map *map);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

public slots:
    void go(); 
    void updatePosition(int direction = Direction::none);  
};
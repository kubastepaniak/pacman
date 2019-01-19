#pragma once
#include "sources/dynamicObject.h"
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QKeyEvent>

#define DEFAULT_X 13
#define DEFAULT_Y 24

class Player : public DynamicObject {
    Q_OBJECT

protected:
    bool moveUpPossible() override;
    bool moveDownPossible() override;
    bool moveLeftPossible() override;
    bool moveRightPossible() override;
    void move(int direction) override;

private:
    QTimer *timer;
    Map *collectablesMap;
    enum DirectAngle { right = 0, left = 180 * 16, 
                       up = 90 * 16, down = -(90 * 16) };
    const static int angle = 60;
    int startAngle = 0;
    int currentDirection;
    int queuedDirection;

    void updateDirection(int direction);
    void updateCoords();
    void checkCollectable();

public:
    int xCoordinate;
    int yCoordinate;
    Player(Map *cMap = nullptr, Map *map = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    void keyPressEvent(QKeyEvent * event);
    
public slots:
    void updatePosition();

signals:
    void itemCollected(int value);
};
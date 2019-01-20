#pragma once
#include "gameObject.h"

#define STEP_RATE 200

class DynamicObject : public GameObject {
    Q_OBJECT
protected:
    int queuedDirection;
    int currentDirection;
    enum Direction { none = 0, right = Qt::Key_Right, left = Qt::Key_Left, up = Qt::Key_Up, down = Qt::Key_Down};
    
    virtual bool moveUpPossible() = 0;
    virtual bool moveDownPossible() = 0;
    virtual bool moveLeftPossible() = 0;
    virtual bool moveRightPossible() = 0;
    virtual void move(int direction) = 0;

    bool moveInDirectionPossible(int direction);
    void updateCoords();
    
public:
    int xPos;
    int yPos;
    int xCoordinate;
    int yCoordinate;
    QTimer *timer;
    DynamicObject(int x, int y, Map *map = nullptr);
    QRectF boundingRect() const override;
};
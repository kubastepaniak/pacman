#pragma once
#include <QGraphicsObject>
#include "gameLogicObject.h"

class GameObject : public QGraphicsObject, public GameLogicObject {
    Q_OBJECT
public:
    GameObject(Map* map = nullptr);
};
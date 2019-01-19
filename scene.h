#pragma once
#include <QGraphicsScene>
#include "map.h"
#include "player.h"
#include "point.h"

class Scene : public QGraphicsScene {
private:
    Map *gameMap;
    Map *collectablesMap;
    Player *player;
    //Point ***pointsMap;
public:
    Scene();
public slots:
    void destroy() {};
};
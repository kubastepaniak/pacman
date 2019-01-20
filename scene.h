#pragma once
#include <QGraphicsScene>
#include "map.h"
#include "player.h"

class Scene : public QGraphicsScene {
private:
    Map *gameMap;
    Map *collectablesMap;
    Player *player;

public:
    Scene();

public slots:
    void destroy();
    void gameOver();
};
#pragma once
#include <QGraphicsScene>
#include "map.h"
#include "player.h"
#include "ghost.h"

class Scene : public QGraphicsScene {
private:
    Map *gameMap;
    Map *collectablesMap;
    Player *player;
    void connectGhost(Ghost *spook);

public:
    Scene();

public slots:
    void destroy();
    void gameOver();
};
#pragma once
#include "sources/dynamicObject.h"
#include "player.h"

class Ghost : public DynamicObject {
    Q_OBJECT

protected:
    Player *player;

    int xCoordinate;
    int yCoordinate;

    enum State { init, chase, avoid };
    int state;
    
    bool moveUpPossible() override;
    bool moveDownPossible() override;
    bool moveLeftPossible() override;
    bool moveRightPossible() override;

public:
    Ghost(int x, int y, Map *map, Player *target);
};
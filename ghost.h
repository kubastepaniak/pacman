#pragma once
#include "sources/dynamicObject.h"
#include "player.h"

class Ghost : public DynamicObject {
    Q_OBJECT

protected:
    Player *player;

    enum State { init, chase, avoid };
    int state;
    
    bool moveUpPossible() override;
    bool moveDownPossible() override;
    bool moveLeftPossible() override;
    bool moveRightPossible() override;
    void move(int direction) override;

    virtual void goWhere() = 0;

    void updateDirection(int direction);
    
public:
    Ghost(int x, int y, Map *map, Player *target);

public slots:
    void changeState();

signals:
    void playerCaught();
};
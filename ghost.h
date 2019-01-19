#pragma once
#include "sources/dynamicObject.h"

class Ghost : public DynamicObject {
    Q_OBJECT

protected:
    int xCoordinate;
    int yCoordinate;
    
    bool moveUpPossible() override;
    bool moveDownPossible() override;
    bool moveLeftPossible() override;
    bool moveRightPossible() override;

public:
    Ghost(int x, int y, Map *map);
};
#pragma once
#include "staticObject.h"

class Collectable : public StaticObject {
    Q_OBJECT
private:
    int points;
    enum Values { point = 1, candy = 3 };
public:
    const static int bgSize = TILESIZE;
    Collectable(int x, int y, int type);
    int getValue();
};
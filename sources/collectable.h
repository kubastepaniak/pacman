#pragma once
#include "staticObject.h"

class Collectable : public StaticObject {
    Q_OBJECT
private:
    int points;
    enum Values { point = 1, candy = 3 };
public:
    const static int bgSize = TILESIZE;

    Collectable(int x, int y, int type) : StaticObject(x, y) {
        if(type == CollTag::point) points = Values::point;
        else if(type == CollTag::candy) points = Values::candy;
    }
    
    int getValue() { return points; }
};
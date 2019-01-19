#include "collectable.h"

Collectable::Collectable(int x, int y, int type)
    : StaticObject(x, y) {
    if(type == CollTag::point) points = Values::point;
    else if(type == CollTag::candy) points = Values::candy;
}

int Collectable::getValue() { return points; }
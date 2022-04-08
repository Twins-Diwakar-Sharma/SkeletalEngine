#ifndef H_CHHALA_OBJ3CT_H
#define H_CHHALA_OBJ3CT_H

#include "Mathril.h"

class RingObject
{
public:
    Vec2 position;
    Vec2 step;
    int scale;
    int tesselatedSize;

    RingObject();
    RingObject(RingObject&);
    RingObject(RingObject&&);
    ~RingObject();
};

#endif
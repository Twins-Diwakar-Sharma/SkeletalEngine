#include "RingObject.h"

RingObject::RingObject()
{}

RingObject::RingObject(RingObject& ro)
{
    position = ro.position;
    step = ro.step;
    scale = ro.scale;
    tesselatedSize = ro.tesselatedSize;
}

RingObject::RingObject(RingObject&& ro)
{
    position = std::move(ro.position);
    step = std::move(ro.step);
    scale = std::move(ro.scale);
    tesselatedSize = std::move(ro.tesselatedSize);
}

RingObject::~RingObject()
{

}
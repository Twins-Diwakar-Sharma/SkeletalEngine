#ifndef H_PR4K4SH_H
#define H_PR4K4SH_H

#include "Mathril.h"
class DirectionalLight
{
private:
    Vec3 direction;
    Vec3 color;
public:
    DirectionalLight();
    DirectionalLight(DirectionalLight&);
    DirectionalLight(DirectionalLight&&);
    DirectionalLight(Vec3&& direction, Vec3&& color);
    DirectionalLight(Vec3& direction, Vec3& color);
    ~DirectionalLight();

    Vec3& getColor();
    Vec3& getDirection();
    void setColor(float r, float g, float b);
    void setDirection(float x, float y, float z);
};

#endif
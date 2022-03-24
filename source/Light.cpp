#include "Light.h"

DirectionalLight::DirectionalLight()
{
    direction[0] = 1;
}

DirectionalLight::DirectionalLight(DirectionalLight& light)
{
    direction = light.direction;
    color = light.color;
}

DirectionalLight::DirectionalLight(DirectionalLight&& light)
{
    direction = std::move(light.direction);
    color = std::move(light.color);
}

DirectionalLight::DirectionalLight(Vec3& direction, Vec3& color)
{
    this->direction = direction;
    this->color = color; 

    float len = (float)direction;
    for(int i=0; i<3; i++)
        direction[i] = direction[i]/len;
}

DirectionalLight::DirectionalLight(Vec3&& direction, Vec3&& color)
{
    this->direction = std::move(direction);
    this->color = std::move(color);

    float len = (float)direction;
    for(int i=0; i<3; i++)
        direction[i] = direction[i]/len;
}

DirectionalLight::~DirectionalLight()
{
}

Vec3& DirectionalLight::getColor()
{
    return color;
}

Vec3& DirectionalLight::getDirection()
{
    return direction;
}

void DirectionalLight::setColor(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void DirectionalLight::setDirection(float x, float y, float z)
{
    direction[0] = x;
    direction[1] = y;
    direction[2] = z;

    float len = (float)direction;
    for(int i=0; i<3; i++)
        direction[i] = direction[i]/len;
}
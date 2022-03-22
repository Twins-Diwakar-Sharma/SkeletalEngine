#include "Renderer.h"

Mat4 proj::perspective;

void proj::setPerspective(float fov, float near, float far, float aspectRatio)
{
    float radFov = fov *  M_PI / (180.0f);

    float d = 1.0f / (tan(radFov / 2.0f));
    perspective[0][0] = d / aspectRatio;
    perspective[1][1] = d;
    perspective[2][2] = (near + far) / (near - far);
    perspective[2][3] = (2 * near * far) / (near - far);
    perspective[3][2] = -1.0f;
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::render()
{

}
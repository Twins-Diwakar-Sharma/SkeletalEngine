#include "Projection.h"

Mat4 proj::perspective;
float proj::near;
float proj::far;
float proj::fov;

void proj::setPerspective(float fov, float near, float far, float aspectRatio)
{
    proj::near = near;
    proj::far = far;
    proj::fov = fov;

    float radFov = fov *  PI / (180.0f);

    float d = 1.0f / (tan(radFov / 2.0f));
    perspective[0][0] = d / aspectRatio;
    perspective[1][1] = d;
    perspective[2][2] = (near + far) / (near - far);
    perspective[2][3] = (2 * near * far) / (near - far);
    perspective[3][2] = -1.0f;

    
}
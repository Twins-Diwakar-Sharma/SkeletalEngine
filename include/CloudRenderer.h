#ifndef BADAL
#define BADAL


#include "Mathril.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Projection.h"
#include "Object.h"
#include <vector>

class CloudRenderer
{
private:
    ShaderProgram* shaderProgram;
public:
    CloudRenderer();
    ~CloudRenderer();  
    void render(Object* cloud, Camera* cam, DirectionalLight* sun);
};

#endif
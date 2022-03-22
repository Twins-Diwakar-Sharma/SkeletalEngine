#include "Renderer.h"

Mat4 proj::perspective;

void proj::setPerspective(float fov, float near, float far, float aspectRatio)
{
    float radFov = fov *  M_PI / (180.0f);

    float d = 1.0f / (tan(radFov / 2.0f));
    perspective[0][0] = d / aspectRatio;
    perspective[1][1] = d;
    perspective[2][2] = (near + far) / (near - far);
    perspective[3][2] = (2 * near * far) / (near - far);
    perspective[2][3] = -1.0f;
}

Renderer::Renderer()
{
    shaderProgram = new ShaderProgram("objects");
    shaderProgram->mapUniform("projection");
}

Renderer::~Renderer()
{
    delete shaderProgram;
}

void Renderer::render(Mesh* mesh)
{
    shaderProgram->use();
    shaderProgram->setUniform("projection",proj::perspective);
    mesh->bind();
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, mesh->indicesSize(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    mesh->unbind();

    shaderProgram->unuse();
}
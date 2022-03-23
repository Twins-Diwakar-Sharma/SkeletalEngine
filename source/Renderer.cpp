#include "Renderer.h"

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
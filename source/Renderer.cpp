#include "Renderer.h"

Renderer::Renderer()
{
    shaderProgram = new ShaderProgram("objects");
    shaderProgram->mapUniform("projection");
    shaderProgram->mapUniform("transform");
    shaderProgram->mapUniform("albedo");
    shaderProgram->mapCameraUniform("cam");
}

Renderer::~Renderer()
{
    delete shaderProgram;
}

void Renderer::render(Object* object, Camera* cam)
{
    shaderProgram->use();
    shaderProgram->setUniform("projection",proj::perspective);
    shaderProgram->setUniform("transform",object->getTransform());
    shaderProgram->setUniform("albedo",0);
    shaderProgram->setUniform("cam",*cam);

    object->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object->getTextureId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, object->size(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    object->unbind();
    
    shaderProgram->unuse();
}
#include "CloudRenderer.h"

CloudRenderer::CloudRenderer()
{
    shaderProgram = new ShaderProgram("clouds");
    shaderProgram->mapUniform("projection");
    shaderProgram->mapUniform("transform");
    shaderProgram->mapUniform("albedo");
    shaderProgram->mapCameraUniform("cam");
    shaderProgram->mapDirectionalLightUniform("sun");
}

CloudRenderer::~CloudRenderer()
{
    delete shaderProgram;
}

void CloudRenderer::render(Object* clouds, Camera* cam, DirectionalLight* sun)
{
    shaderProgram->use();
    shaderProgram->setUniform("projection",proj::perspective);
    shaderProgram->setUniform("albedo",0);
    shaderProgram->setUniform("cam",*cam);
    shaderProgram->setUniform("sun", *sun);

         shaderProgram->setUniform("transform",clouds->getTransform());
            clouds->bind();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, clouds->getTextureId());
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glDrawElements(GL_TRIANGLES, clouds->size(), GL_UNSIGNED_INT, 0);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(0);
            clouds->unbind();
   

    shaderProgram->unuse();
}
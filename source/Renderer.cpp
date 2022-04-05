#include "Renderer.h"

Renderer::Renderer()
{
    shaderProgram = new ShaderProgram("objects");
    shaderProgram->mapUniform("projection");
    shaderProgram->mapUniform("transform");
    shaderProgram->mapUniform("albedo");
    shaderProgram->mapCameraUniform("cam");
    shaderProgram->mapDirectionalLightUniform("sun");
}

Renderer::~Renderer()
{
    delete shaderProgram;
}

void Renderer::render(std::vector<Object*>& objects, Camera* cam, DirectionalLight* sun)
{
    shaderProgram->use();
    shaderProgram->setUniform("projection",proj::perspective);
    shaderProgram->setUniform("albedo",0);
    shaderProgram->setUniform("cam",*cam);
    shaderProgram->setUniform("sun", *sun);

    for(int i=0; i<objects.size(); i++)
    {
            shaderProgram->setUniform("transform",objects[i]->getTransform());
            objects[i]->bind();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, objects[i]->getTextureId());
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glDrawElements(GL_TRIANGLES, objects[i]->size(), GL_UNSIGNED_INT, 0);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(0);
            objects[i]->unbind();
    }
    
    shaderProgram->unuse();
}
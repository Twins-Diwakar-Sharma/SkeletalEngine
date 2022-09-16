#include "SkyboxRenderer.h"

SkyboxRenderer::SkyboxRenderer() : shaderProgram("skybox")
{
    skyboxMesh.createSkybox();
    shaderProgram.mapUniform("projection");
    shaderProgram.mapUniform("skybox");
    shaderProgram.mapCameraUniform("cam");
}

SkyboxRenderer::~SkyboxRenderer()
{

} 

void SkyboxRenderer::render(Texture& skyboxTexture, Camera& cam)
{
    shaderProgram.use();
    shaderProgram.setUniform("projection",proj::perspective);
    shaderProgram.setUniform("skybox",0);
    shaderProgram.setUniform("cam", cam);


    glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture.getTextureId());

    skyboxMesh.bind();
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(0);
    skyboxMesh.unbind();
    glDepthMask(GL_TRUE);

    shaderProgram.unuse();
}
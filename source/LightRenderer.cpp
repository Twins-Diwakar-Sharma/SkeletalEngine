#include "LightRenderer.h"

LightRenderer::LightRenderer() : shaderProgram("light")
{
    shaderProgram.mapUniform("gPosition");
    shaderProgram.mapUniform("gAlbedo");
    shaderProgram.mapUniform("gNormal");
    shaderProgram.mapUniform("ambientOcclusion");
    shaderProgram.mapCameraUniform("cam");
    shaderProgram.mapDirectionalLightUniform("sun");
}

LightRenderer::~LightRenderer()
{}

void LightRenderer::render(Mesh& quad, Framebuffer& deferredShadingFramebuffer, Framebuffer& aoFramebuffer, DirectionalLight& sun, Camera& cam)
{
    shaderProgram.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, deferredShadingFramebuffer.getColorAttachmentId(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, deferredShadingFramebuffer.getColorAttachmentId(1));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, deferredShadingFramebuffer.getColorAttachmentId(2));
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, aoFramebuffer.getColorAttachmentId(0));
    shaderProgram.setUniform("gPosition",0);
    shaderProgram.setUniform("gAlbedo",1);
    shaderProgram.setUniform("gNormal",2);
    shaderProgram.setUniform("ambientOcclusion",3);
    shaderProgram.setUniform("sun",sun);
    shaderProgram.setUniform("cam",cam);
    quad.bind();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, quad.indicesSize(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    quad.unbind();
    shaderProgram.unuse();
}
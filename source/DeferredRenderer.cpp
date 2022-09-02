#include "DeferredRenderer.h"

DeferredRenderer::DeferredRenderer() : shaderProgram("deferred")
{
    quad.createPlane2D();
    shaderProgram.mapUniform("gPosition");
    shaderProgram.mapUniform("gAlbedo");
    shaderProgram.mapUniform("gNormal");
}

DeferredRenderer::~DeferredRenderer()
{}

void DeferredRenderer::render(Framebuffer& deferredShadingFramebuffer)
{
    shaderProgram.use();
    deferredShadingFramebuffer.bindTextures();
    shaderProgram.setUniform("gPosition",0);
    shaderProgram.setUniform("gAlbedo",1);
    shaderProgram.setUniform("gNormal",2);
    quad.bind();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, quad.indicesSize(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    quad.unbind();
    shaderProgram.unuse();
}
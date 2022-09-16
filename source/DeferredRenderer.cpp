#include "DeferredRenderer.h"

DeferredRenderer::DeferredRenderer() : shaderProgram("deferred")
{
    shaderProgram.mapUniform("gAlbedo");
}

DeferredRenderer::~DeferredRenderer()
{}

void DeferredRenderer::render(Mesh& quad, Framebuffer& deferredShadingFramebuffer)
{
    shaderProgram.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, deferredShadingFramebuffer.getColorAttachmentId(0));
    shaderProgram.setUniform("gAlbedo",0);
    quad.bind();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, quad.indicesSize(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    quad.unbind();
    shaderProgram.unuse();
}
#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer()
{
    ringShaderProgram = new ShaderProgram("terrainRing",TESS);
    ringShaderProgram->mapUniform("projection");
    //shaderProgram->mapUniform("transform");
    //shaderProgram->mapUniform("albedo");
    ringShaderProgram->mapCameraUniform("cam");
    //shaderProgram->mapDirectionalLightUniform("sun");
    ringShaderProgram->mapUniform("size");
}

TerrainRenderer::~TerrainRenderer()
{
    delete ringShaderProgram;
}

void TerrainRenderer::render(RingMesh* ringMesh, Camera* cam, int size)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ringShaderProgram->use();

	glPatchParameteri(GL_PATCH_VERTICES, 4);

	ringShaderProgram->setUniform("projection", proj::perspective);
	ringShaderProgram->setUniform("cam", *cam);
    ringShaderProgram->setUniform("size", size);

    ringMesh->bind();
    glEnableVertexAttribArray(0);
    glDrawElements(GL_PATCHES, ringMesh->indicesSize(), GL_UNSIGNED_INT, 0);  
    glDisableVertexAttribArray(0);
    ringMesh->unbind();

    ringShaderProgram->unuse();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
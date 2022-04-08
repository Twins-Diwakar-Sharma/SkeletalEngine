#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer()
{
    ringShaderProgram = new ShaderProgram("terrainRing",TESS);
    ringShaderProgram->mapUniform("projection");
    ringShaderProgram->mapCameraUniform("cam");
    ringShaderProgram->mapUniform("size");
    ringShaderProgram->mapUniform("LOD");
    ringShaderProgram->mapUniform("position");
}

TerrainRenderer::~TerrainRenderer()
{
    delete ringShaderProgram;
}

void TerrainRenderer::render(TerrainMesh* terrainMesh, Camera* cam, int size)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    ringShaderProgram->use();

    ringShaderProgram->setUniform("LOD", 1);
	ringShaderProgram->setUniform("projection", proj::perspective);
	ringShaderProgram->setUniform("cam", *cam);
    ringShaderProgram->setUniform("size", size);

    terrainMesh->bind();
    glEnableVertexAttribArray(0);
    glDrawElements(GL_PATCHES, terrainMesh->indicesSize(), GL_UNSIGNED_INT, 0);  
    glDisableVertexAttribArray(0);
    terrainMesh->unbind();

    ringShaderProgram->unuse();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TerrainRenderer::render(Terrain* terrain, Camera* cam)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    ringShaderProgram->use();

    ringShaderProgram->setUniform("LOD", terrain->getLod());
	ringShaderProgram->setUniform("projection", proj::perspective);
	ringShaderProgram->setUniform("cam", *cam);
    //ringShaderProgram->setUniform("size", 2);

    terrain->bindPlatformMesh();
    glEnableVertexAttribArray(0);
    ringShaderProgram->setUniform("size", terrain->getPlanes(0)->scale);
    ringShaderProgram->setUniform("position", terrain->getPlanes(0)->position);
    glDrawElements(GL_PATCHES, terrain->getPlatformMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
    glDisableVertexAttribArray(0);
    terrain->unbindMesh();

    terrain->bindRingMesh();
    for(int i=1; i<terrain->getNoOfRings()+1; i++)
    {
        glEnableVertexAttribArray(0);
        ringShaderProgram->setUniform("size",terrain->getPlanes(i)->scale);
        ringShaderProgram->setUniform("position", terrain->getPlanes(i)->position);
        glDrawElements(GL_PATCHES, terrain->getRingMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
        glDisableVertexAttribArray(0);
    }
    terrain->unbindMesh();

    ringShaderProgram->unuse();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
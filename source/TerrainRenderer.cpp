#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer()
{
    ringShaderProgram = new ShaderProgram("terrainRing",TESS);
    ringShaderProgram->mapUniform("projection");
    ringShaderProgram->mapCameraUniform("cam");
    ringShaderProgram->mapUniform("size");
    ringShaderProgram->mapUniform("LOD");
    ringShaderProgram->mapUniform("position");

    plankShaderProgram = new ShaderProgram("terrainPlank",TESS);
    plankShaderProgram->mapUniform("projection");
    plankShaderProgram->mapCameraUniform("cam");
    plankShaderProgram->mapUniform("size");
    plankShaderProgram->mapUniform("LOD");
    plankShaderProgram->mapUniform("position");
    plankShaderProgram->mapUniform("rotate");
}

TerrainRenderer::~TerrainRenderer()
{
    delete ringShaderProgram;
}

void TerrainRenderer::render(Terrain* terrain, Camera* cam)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    ringShaderProgram->use();

    ringShaderProgram->setUniform("LOD", terrain->getLod());
	ringShaderProgram->setUniform("projection", proj::perspective);
	ringShaderProgram->setUniform("cam", *cam);

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

    // render planks now
    renderPlanks(terrain, cam);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TerrainRenderer::renderPlanks(Terrain* terrain, Camera* cam)
{

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    plankShaderProgram->use();

    plankShaderProgram->setUniform("LOD", terrain->getLod());
	plankShaderProgram->setUniform("projection", proj::perspective);
	plankShaderProgram->setUniform("cam", *cam);

    Vec2 size(8,2);    // size should be Vec2(size, tesselatedSize)
    terrain->bindPlankMesh();

    for(int i=0; i<terrain->getNoOfRings()+1; i++)
    {
        size[0] = terrain->getPlanes(i)->scale;
        size[1] = terrain->getPlanes(i)->tesselatedSize;
        plankShaderProgram->setUniform("size", size);

        if(terrain->getPlanes(i)->step[1] != 0)
        {
            glEnableVertexAttribArray(0);
            plankShaderProgram->setUniform("position", terrain->getPlanes(i)->horizontalPlank.position);
            plankShaderProgram->setUniform("rotate",0);
            glDrawElements(GL_PATCHES, terrain->getPlankMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
            glDisableVertexAttribArray(0);
        }

        if(terrain->getPlanes(i)->step[0] != 0)
        {
            glEnableVertexAttribArray(0);
            plankShaderProgram->setUniform("position", terrain->getPlanes(i)->verticalPlank.position);
            plankShaderProgram->setUniform("rotate",1);
            glDrawElements(GL_PATCHES, terrain->getPlankMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
            glDisableVertexAttribArray(0);
        }
    }
    terrain->unbindMesh();

    plankShaderProgram->unuse();
}
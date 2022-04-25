#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer()
{
    ringShaderProgram = new ShaderProgram("terrainRing",TESS);
    ringShaderProgram->mapUniform("projection");
    ringShaderProgram->mapCameraUniform("cam");
    ringShaderProgram->mapUniform("size");
    ringShaderProgram->mapUniform("LOD");
    ringShaderProgram->mapUniform("position");
    ringShaderProgram->mapUniform("heightMap");
    ringShaderProgram->mapUniform("heightMapSize");
    ringShaderProgram->mapDirectionalLightUniform("sun");
    ringShaderProgram->mapUniform("step");
    ringShaderProgram->mapUniform("tesselatedSize");

    plankShaderProgram = new ShaderProgram("terrainPlank",TESS);
    plankShaderProgram->mapUniform("projection");
    plankShaderProgram->mapCameraUniform("cam");
    plankShaderProgram->mapUniform("size");
    plankShaderProgram->mapUniform("LOD");
    plankShaderProgram->mapUniform("position");
    plankShaderProgram->mapUniform("rotate");
    plankShaderProgram->mapUniform("heightMap");
    plankShaderProgram->mapUniform("heightMapSize");
    plankShaderProgram->mapDirectionalLightUniform("sun");
    plankShaderProgram->mapUniform("step");
}

TerrainRenderer::~TerrainRenderer()
{
    delete ringShaderProgram;
}

void TerrainRenderer::render(Terrain* terrain, Camera* cam, HeightMap* heightMap, DirectionalLight* sun)
{
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    ringShaderProgram->use();

    ringShaderProgram->setUniform("LOD", terrain->getLod());
	ringShaderProgram->setUniform("projection", proj::perspective);
	ringShaderProgram->setUniform("cam", *cam);
    ringShaderProgram->setUniform("heightMap",0);
    ringShaderProgram->setUniform("heightMapSize", heightMap->mapSize);
    ringShaderProgram->setUniform("sun", *sun);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightMap->getTextureId());

    terrain->bindPlatformMesh();
    glEnableVertexAttribArray(0);
    ringShaderProgram->setUniform("size", terrain->getPlanes(0)->scale);
    ringShaderProgram->setUniform("position", terrain->getPlanes(0)->position);
    ringShaderProgram->setUniform("step", terrain->getPlanes(0)->step);
    ringShaderProgram->setUniform("tesselatedSize", terrain->getPlanes(0)->tesselatedSize);
    glDrawElements(GL_PATCHES, terrain->getPlatformMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
    glDisableVertexAttribArray(0);
    terrain->unbindMesh();

    terrain->bindRingMesh();
    for(int i=1; i<terrain->getNoOfRings()+1; i++)
    {
        glEnableVertexAttribArray(0);
        ringShaderProgram->setUniform("size",terrain->getPlanes(i)->scale);
        ringShaderProgram->setUniform("position", terrain->getPlanes(i)->position);
        ringShaderProgram->setUniform("step", terrain->getPlanes(i)->step);
        ringShaderProgram->setUniform("tesselatedSize", terrain->getPlanes(i)->tesselatedSize);
        glDrawElements(GL_PATCHES, terrain->getRingMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
        glDisableVertexAttribArray(0);
    }
    terrain->unbindMesh();

    ringShaderProgram->unuse();

    // render planks now
    renderPlanks(terrain, cam, heightMap, sun);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TerrainRenderer::renderPlanks(Terrain* terrain, Camera* cam, HeightMap* heightMap, DirectionalLight* sun)
{

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    plankShaderProgram->use();

    plankShaderProgram->setUniform("LOD", terrain->getLod());
	plankShaderProgram->setUniform("projection", proj::perspective);
	plankShaderProgram->setUniform("cam", *cam);
    plankShaderProgram->setUniform("heightMap",0);
    plankShaderProgram->setUniform("heightMapSize", heightMap->mapSize);
    plankShaderProgram->setUniform("sun", *sun);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightMap->getTextureId());



    Vec2 size(1,1);    // size should be Vec2(size, tesselatedSize)
    terrain->bindPlankMesh();


    for(int i=0; i<terrain->getNoOfRings()+1; i++)
    {
        size[0] = terrain->getPlanes(i)->scale;
        size[1] = terrain->getPlanes(i)->tesselatedSize;
        plankShaderProgram->setUniform("size", size);
        plankShaderProgram->setUniform("step", terrain->getPlanes(i)->step);

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
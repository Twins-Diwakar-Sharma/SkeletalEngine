#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer() : ringShaderProgram("terrainRing", GEOTESS)
{
    ringShaderProgram.mapUniform("projection");
    ringShaderProgram.mapCameraUniform("cam");
    ringShaderProgram.mapUniform("size");
    ringShaderProgram.mapUniform("LOD");
    ringShaderProgram.mapUniform("position");
    ringShaderProgram.mapDirectionalLightUniform("sun");
    ringShaderProgram.mapUniform("step");
    ringShaderProgram.mapUniform("tesselatedSize");
}

TerrainRenderer::~TerrainRenderer()
{

}

void TerrainRenderer::render(Terrain& terrain, Camera& cam, DirectionalLight& sun)
{

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    ringShaderProgram.use();

    ringShaderProgram.setUniform("LOD", terrain.getLod());
	ringShaderProgram.setUniform("projection", proj::perspective);
	ringShaderProgram.setUniform("cam", cam);
    ringShaderProgram.setUniform("sun", sun);

    terrain.bindPlatformMesh();
    glEnableVertexAttribArray(0);
    ringShaderProgram.setUniform("size", terrain.getPlanes(0)->scale);
    ringShaderProgram.setUniform("position", terrain.getPlanes(0)->position);
    ringShaderProgram.setUniform("step", terrain.getPlanes(0)->step);
    ringShaderProgram.setUniform("tesselatedSize", terrain.getPlanes(0)->tesselatedSize);
    glDrawElements(GL_PATCHES, terrain.getPlatformMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
    glDisableVertexAttribArray(0);
    terrain.unbindMesh();

    terrain.bindRingMesh();
    for(int i=1; i<terrain.getNoOfRings()+1; i++)
    {
        glEnableVertexAttribArray(0);
        ringShaderProgram.setUniform("size",terrain.getPlanes(i)->scale);
        ringShaderProgram.setUniform("position", terrain.getPlanes(i)->position);
        ringShaderProgram.setUniform("step", terrain.getPlanes(i)->step);
        ringShaderProgram.setUniform("tesselatedSize", terrain.getPlanes(i)->tesselatedSize);
        glDrawElements(GL_PATCHES, terrain.getRingMeshIndicesSize(), GL_UNSIGNED_INT, 0);  
        glDisableVertexAttribArray(0);
    }
    terrain.unbindMesh();

    ringShaderProgram.unuse();
}
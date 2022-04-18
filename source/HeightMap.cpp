#include "HeightMap.h"

HeightMap::HeightMap()
{

}

HeightMap::~HeightMap()
{
    if(heightMapTexture)
        delete heightMapTexture;
}

void HeightMap::setHeightMapTexture(std::string path)
{
    if(heightMapTexture)
    {
        delete heightMapTexture;
    }
    heightMapTexture = new Texture(path);
}

unsigned int HeightMap::getTextureId()
{
    return heightMapTexture->getTextureId();
}
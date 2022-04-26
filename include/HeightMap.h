#ifndef H_H31GHT_M4P_H
#define H_H31GHT_M4P_H

#include "Texture.h"

class HeightMap
{
private:
    Texture* heightMapTexture=nullptr;
public:
    HeightMap();
    ~HeightMap();
    void setHeightMapTexture(std::string path);
    unsigned int getTextureId();
    const int mapSize = 1024;
};

#endif
#ifndef H_3N61N3_H
#define H_3N61N3_H

#include <map>
#include <iostream>
#include <time.h>
#include <thread>
#include "Renderer.h"
#include "Light.h"
#include <vector>
#include "RingMesh.h"
#include "PlatformMesh.h"
#include "TerrainRenderer.h"
#include "PlankMesh.h"
#include "CloudRenderer.h"

#include "Window.h"
class Engine
{
private:
    float fps = 120.0f;
    float ms_per_update=1000.0f/fps;

    Window* window;
    Camera* cam;

    float translateForward, translateSide;
	float transVal = 1.0f;
	float rotx, roty;

    void initialize();
    void clean();
    void update();
    void input();
    void render(double);

    Renderer* objectsRenderer;

    DirectionalLight* sun;

    std::vector<Object*> objects;
    std::vector<Mesh*> meshes;
    std::vector<Texture*> textures;

    // Problem makers
    TerrainRenderer* terrainRenderer;
    Terrain* terrain;
    CloudRenderer* cloudRenderer;
    Object* clouds;

    bool hold=false;
    bool wireframe=false;
    bool updateTerrain=true;

public:
    Engine();
    ~Engine();
    void loop();
};

#endif

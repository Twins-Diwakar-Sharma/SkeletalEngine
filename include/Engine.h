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
#include "CloudRenderer.h"
#include "Window.h"
#include "Debug.h"
#include "Framebuffer.h"
#include "DeferredRenderer.h"
#include "LightRenderer.h"
#include "SkyboxRenderer.h"
#include "HBAORenderer.h"


class Engine
{
private:
    float fps = 120.0f;
    float ms_per_update=1000.0f/fps;

    Window window;
    Camera cam;

    DirectionalLight sun;

    float translateForward, translateSide;
	float transVal = 0.1f;
	float rotx, roty;

    void initialize();
    void clean();
    void update();
    void input();
    void render(double);

    Renderer objectsRenderer;


    std::vector<Object> objects;

    std::map<std::string, Mesh> meshMap;
    std::map<std::string, Texture> textureMap;

    // Problem makers
    TerrainRenderer terrainRenderer;
    Terrain terrain;
    CloudRenderer* cloudRenderer;
    Object* clouds;

    bool hold=false;
    bool wireframe=false;
    bool updateTerrain=true;

    Mesh screenQuad;
    Framebuffer deferredShadingFramebuffer;
    Framebuffer hbaoFramebuffer;
    Framebuffer lightFramebuffer;

    LightRenderer lightRenderer;
    DeferredRenderer deferredRenderer;
    SkyboxRenderer skyboxRenderer;
    HBAORenderer hbaoRenderer;

    Texture skyboxTexture;

public:
    Engine();
    ~Engine();
    void loop();
};

#endif

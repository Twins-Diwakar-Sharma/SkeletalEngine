#ifndef H_3N61N3_H
#define H_3N61N3_H

#include <map>
#include <iostream>
#include <time.h>
#include <thread>
#include "Window.h"
#include "Renderer.h"
#include "Light.h"
#include <vector>
#include "RingMesh.h"
//#include "TerrainRenderer.h"

class Engine
{
private:
    //std::thread* loopThread;
    float fps = 120.0f;
    float ms_per_update=1000.0f/fps;

    Window* window;
    Camera* cam;

    float translateForward, translateSide;
	float transVal = 0.05f;
	float rotx, roty;

    void initialize();
    void clean();
    void update();
    void input();
    void render(double);

    Renderer* objectsRenderer;

    DirectionalLight* sun;

    std::vector<Object*> objects;
    std::map<std::string,Texture*> textureMap;
    std::map<std::string,Mesh*> meshMap;
    
public:
    Engine();
    ~Engine();
    void loop();
};

#endif

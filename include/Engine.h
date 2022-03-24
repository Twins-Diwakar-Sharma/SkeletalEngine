#ifndef H_3N61N3_H
#define H_3N61N3_H

#include <iostream>
#include <time.h>
#include <thread>
#include "Window.h"
#include "Renderer.h"
#include "Light.h"
#include <vector>

class Engine
{
private:
    std::thread* loopThread;
    float fps = 120.0f;
    float ms_per_update=1000.0f/fps;

    Window* window;
    Camera* cam;

    float translateForward, translateSide;
	float transVal = 0.05f;
	float rotx, roty;

    void initialize();
    void update();
    void input();
    void render(double);

    Object* testObject;
    Renderer* objectsRenderer;

    Object* plane;
    DirectionalLight* sun;

    std::vector<Object*> objects;

public:
    Engine();
    ~Engine();
    void loop();
};

#endif

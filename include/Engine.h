#ifndef H_3N61N3_H
#define H_3N61N3_H

#include <iostream>
#include <time.h>
#include <thread>
#include "Window.h"
#include "Renderer.h"

class Engine
{
private:
    std::thread* loopThread;
    float fps = 120.0f;
    float ms_per_update=1000.0f/fps;

    Window* window;

    void initialize();
    void update();
    void input();
    void render(double);

    Mesh* testMesh;
    Renderer* objectsRenderer;

public:
    Engine();
    ~Engine();
    void loop();
};

#endif

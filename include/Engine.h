#ifndef H_3N61N3_H
#define H_3N61N3_H

#include <iostream>
#include <time.h>
#include <thread>
#include "Window.h"

class Engine
{
private:
    std::thread* loopThread;
    float fps = 120.0f;
    float ms_per_update=1000.0f/fps;
    static int width,height;

    Window* window;

    void initialize();
    void update();
    void input();
    void render(double);


public:
    Engine();
    ~Engine();
    void loop();
};

#endif

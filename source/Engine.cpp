#include "Engine.h"

int Engine::width = 512;
int Engine::height = 512;

Engine::Engine()
{
    Engine::width = 800;
    Engine::height = 600;
    loopThread = new std::thread(&Engine::loop, this);
}

Engine::~Engine()
{

}

void Engine::loop()
{
    clock_t prev = clock();
    double elapsed = 0, lag = 0;
    clock_t curr = clock();
    initialize();


    while(true) // ! window close
    {
        elapsed = ((double)curr - (double)prev) * 1000 / CLOCKS_PER_SEC;
		lag += elapsed;
		prev = clock();

        input();
        while(lag >= ms_per_update)
        {
            update();
            lag -= ms_per_update;
        }
        render(lag/ms_per_update);
        curr = clock();
    }
}

void Engine::initialize()
{
    window = new Window(Engine::width,Engine::height);
    
}

void Engine::input()
{

    window->pollEvents();
}

void Engine::update()
{

}

void Engine::render(double dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window->swap();
}

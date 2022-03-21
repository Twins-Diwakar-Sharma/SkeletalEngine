#include "Engine.h"

Engine::Engine()
{
    loopThread = new std::thread(&Engine::loop, this);
    loopThread->join();
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

    std::cout << "Loop start" << std::endl;
    while(!window->close()) // ! window close
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
    std::cout << "Loop end" << std::endl;
}

void Engine::initialize()
{
    window = new Window();
    
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

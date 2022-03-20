#include "Engine.h"

Engine::Engine()
{

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

}

void Engine::input()
{

}

void Engine::update()
{

}

void Engine::render(double dt)
{
    
}

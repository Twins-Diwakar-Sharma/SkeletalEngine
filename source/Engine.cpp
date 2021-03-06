#include "Engine.h"

Engine::Engine()
{
    //loopThread = new std::thread(&Engine::loop, this);
    //loopThread->join();
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
    proj::setPerspective(60.0f,0.1f,1000.0f,window->getAspect());
    
    window = new Window();
    objectsRenderer = new Renderer();
    Mesh* testMesh = new Mesh("alpine");

    Texture* testTexture = new Texture("alpine");

    testObject = new Object(testMesh,testTexture);

    testObject->setScale(0.2f,0.2f,0.2f);
    testObject->setPosition(0,-2,-8);
    objects.push_back(testObject);

    Mesh* planeMesh = new Mesh();
    planeMesh->createPlane();
    Texture* planeTex = new Texture("path");
    plane = new Object(planeMesh,planeTex);
    plane->setPosition(0,-2,-8);
    plane->setScale(25,0,25);
    objects.push_back(plane);

    cam = new Camera();
	cam->setPosition(0,1,0);

    sun = new DirectionalLight(Vec3(-1,-0.5,0),Vec3(1,1,1));

    glEnable(GL_DEPTH_TEST);
}

void Engine::input()
{
    window->handleKey(translateForward, translateSide, transVal);
	window->handleMouse(rotx, roty);

    window->pollEvents();
}   

void Engine::update()
{
    cam->rotate(rotx, roty, 0);
	rotx = 0;	roty = 0;
	cam->translate(translateForward, translateSide);

    testObject->rotate(0,1,0);
    translateForward = 0; translateSide = 0;
}

void Engine::render(double dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectsRenderer->render(objects, cam, sun);
    window->swap();
}

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
    clean();
    std::cout << "Loop end" << std::endl;
}

void Engine::initialize()
{
    proj::setPerspective(60.0f,0.1f,1000.0f,window->getAspect());
    
    window = new Window();
    objectsRenderer = new Renderer();

    Mesh* testMesh = new Mesh("alpine");
    meshes.push_back(testMesh);
    Texture* testTexture = new Texture("alpine");
    textures.push_back(testTexture);
    Object* testObject = new Object(testMesh,testTexture);
    testObject->setScale(0.2f,0.2f,0.2f);
    testObject->setPosition(0,-2,-8);
    objects.push_back(testObject);

    Mesh* planeMesh = new Mesh();
    planeMesh->createPlane();
    meshes.push_back(planeMesh);
    Texture* planeTex = new Texture("path");
    textures.push_back(planeTex);
    Object* plane = new Object(planeMesh,planeTex);
    plane->setPosition(0,-2,-8);
    plane->setScale(25,0,25);
    objects.push_back(plane);

    cam = new Camera();
	cam->setPosition(0,1,0);

    sun = new DirectionalLight(Vec3(-1,-0.5,0),Vec3(1,1,1));

    glClearColor(0.8f,0.9f,1,1);
    glEnable(GL_DEPTH_TEST);


    // problem makers 
    terrain = new Terrain();
    terrain->reconfigure(32,8);
    terrainRenderer = new TerrainRenderer();
    plank = new PlankMesh();
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

    objects[0]->rotate(0,1,0);
    terrain->update(cam->position);

    translateForward = 0; translateSide = 0;
}

void Engine::render(double dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectsRenderer->render(objects, cam, sun);
    terrainRenderer->render(terrain,cam);
    window->swap();
}

void Engine::clean()
{
     for(int i=0; i<objects.size(); i++)
     {
        delete objects[i];
     }
     for(int i=0; i<meshes.size(); i++)
     {
         delete meshes[i];
     }
     for(int i=0; i<textures.size(); i++)
     {
         delete textures[i];
     }
    delete window;
    delete cam;
    delete objectsRenderer;
     
}

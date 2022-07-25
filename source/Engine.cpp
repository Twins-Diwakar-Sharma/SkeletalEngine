#include "Engine.h"

Engine::Engine()
            : sun(Vec3(-1,-1,-1),Vec3(1,1,0.9))
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

    LOG("Loop start");

    while(!window.close()) // ! window close
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
    
    LOG("Loop end");
}

void Engine::initialize()
{
    proj::setPerspective(60.0f,0.1f,1000.0f,window.getAspect());
    
   // cloudRenderer = new CloudRenderer();

    meshMap.emplace("alpine", "alpine");
    textureMap.emplace("alpine", "alpine");
    objects.emplace_back(meshMap["alpine"], textureMap["alpine"]);
    objects[0].setScale(0.2f,0.2f,0.2f);
    objects[0].setPosition(0,0,0);

    meshMap.emplace("plane", Mesh());
    meshMap["plane"].createPlane();
    textureMap.emplace("path","path");
    objects.emplace_back(meshMap["plane"], textureMap["path"]);
    objects[1].scale(10,1,10);

/*
    clouds = new Object(planeMesh,planeTex);
    clouds->setPosition(0,100,0);
    clouds->setScale(500,0,500);
*/
    
	cam.setPosition(0,1,0);

    glClearColor(0.8f,0.9f,1,1);
    glEnable(GL_DEPTH_TEST);


    // problem makers 
    terrain = new Terrain();
    terrain->reconfigure(128,16);  
    terrainRenderer = new TerrainRenderer();

}

void Engine::input()
{
    window.handleKey(translateForward, translateSide, transVal);
	window.handleMouse(rotx, roty);
    window.handleHold(hold);
    window.handleTerrainUpdate(updateTerrain);
    window.handleWireframe(wireframe);
    window.pollEvents();
}   

void Engine::update()
{
    if(hold)
    {
        cam.setPosition(0,0,0);
        rotx = 0; roty = 0;
        cam.spin[0] = 1; cam.spin[1] = 0; cam.spin[2] = 0; cam.spin[3] = 0;
    }
    else
    {
        cam.rotate(rotx, roty, 0);
	    rotx = 0;	roty = 0;
	    cam.translate(translateForward, translateSide);
    }
    
    objects[0].rotate(0,1,0);
  //  clouds->setPosition(cam.position[0],100,cam.position[2]);
    
    if(updateTerrain)
        terrain->update(cam.position);

    translateForward = 0; translateSide = 0;
}

void Engine::render(double dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectsRenderer.render(objects, cam, sun);
    if(wireframe)
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   // cloudRenderer->render(clouds,cam,sun);
     terrainRenderer->render(terrain,&cam,&sun);
    window.swap();
}

void Engine::clean()
{    
}

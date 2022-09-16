#include "Engine.h"

Engine::Engine()
            : sun(Vec3(-1,-1,-1),Vec3(1,1,0.8))
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

    objects.emplace_back(meshMap["alpine"], textureMap["alpine"]);
    objects[1].setScale(0.25f,0.25f,0.25f);
    objects[1].setPosition(1,0,0.5f);
/*
    clouds = new Object(planeMesh,planeTex);
    clouds->setPosition(0,100,0);
    clouds->setScale(500,0,500);
*/
    
	cam.setPosition(0,1,0);

    glClearColor(0.8f,0.9f,1,1);
    glEnable(GL_DEPTH_TEST);

    terrain.reconfigure(128,16);  

    // post processing
    screenQuad.createPlane2D();
    deferredShadingFramebuffer.setWidth(window.getWidth());
    deferredShadingFramebuffer.setHeight(window.getHeight());
    deferredShadingFramebuffer.attachColorTexture(GL_RGBA16, GL_RGBA);
    deferredShadingFramebuffer.attachColorTexture(GL_RGBA16, GL_RGBA);
    deferredShadingFramebuffer.attachColorTexture(GL_RGBA16, GL_RGBA);
    deferredShadingFramebuffer.setDrawBuffers();
    deferredShadingFramebuffer.attachDepthRender();

    lightFramebuffer.setWidth(window.getWidth());
    lightFramebuffer.setHeight(window.getHeight());
    lightFramebuffer.attachColorTexture(GL_RGBA16, GL_RGBA);
    lightFramebuffer.setDrawBuffers();

    skyboxTexture.generateCubeMap("lake");

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
    
   // objects[0].rotate(0,1,0);
  //  clouds->setPosition(cam.position[0],100,cam.position[2]);
    
    if(updateTerrain)
        terrain.update(cam.position);

    translateForward = 0; translateSide = 0;
}

void Engine::render(double dt)
{
    deferredShadingFramebuffer.use();
    deferredShadingFramebuffer.bindViewport();
    glClearColor(0.8f,0.9f,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(wireframe)
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    skyboxRenderer.render(skyboxTexture, cam); // always first, skybox is somehow dependent
    objectsRenderer.render(objects, cam);
    terrainRenderer.render(terrain, cam);

    deferredShadingFramebuffer.unuse();

    lightFramebuffer.use();
    lightFramebuffer.bindViewport();
    glClearColor(0.8f,0.9f,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    lightRenderer.render(screenQuad, deferredShadingFramebuffer, sun, cam);
    lightFramebuffer.unuse();


    glViewport(0, 0, window.getWidth(), window.getHeight());
    glClearColor(0.8f,0.9f,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    deferredRenderer.render(screenQuad, lightFramebuffer);

    window.swap();
}

void Engine::clean()
{    
}

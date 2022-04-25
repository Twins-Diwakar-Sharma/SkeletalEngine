#ifndef KHIDKI
#define KHIDKI

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Projection.h"

class Window
{
private:
    GLFWwindow* win;
    static int width, height;
    const char* title="Skeletal Engine";
    void static resize(GLFWwindow* w, int width, int height);
    float senstivity = 0.05f;

public:
    Window();
    bool close();
    void terminate();
    void swap();
    float getAspect();
    void handleKey(float& t, float& s, float val);
    void handleMouse(float& rx, float& ry);
    void pollEvents();

    void handleHold(bool& hold);
    void handleWireframe(bool& wireframe);
    void handleTerrainUpdate(bool& terrainUpdate);
};

#endif
#ifndef KHIDKI
#define KHIDKI

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
    GLFWwindow* win;
    int width=800, height=600;
    const char* title="Skeletal Engine";
    void static resize(GLFWwindow* w, int width, int height);
    float senstivity = 0.05f;

public:
    Window();
    Window(int width, int height);
    bool close();
    void terminate();
    void swap();
    float getAspect();
    void handleKey(float& t, float& s, float val);
    void handleMouse(float& rx, float& ry);
};

#endif
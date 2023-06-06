#ifndef BOOP_RENDER_H
#define BOOP_RENDER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

extern GLFWwindow * window;

void construct_renderer();
void render();

#endif

#include "context.h"
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>

GLFWwindow * window;

void construct_context() {
	if(!glfwInit()) {
		puts("glfwInit() failed");
		exit(1);
	}
	atexit(glfwTerminate);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // TODO check version
	// TODO GLFW_X11_CLASS/INSTANCE_NAME
	window = glfwCreateWindow(1920, 1080, "Boop", nullptr, nullptr);
	char const * error_message;
	if(glfwGetError(&error_message)) {
		fprintf(stderr, "glfwCreateWindow() failed: %s", error_message);
		exit(1);
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGL(glfwGetProcAddress)) {
		puts("gladLoadGL() failed");
		exit(1);
	}
	// glfwSwapInterval(0);
}

#include "render.h"

int main() {
	construct_renderer();
	while(!glfwWindowShouldClose(window)) {
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

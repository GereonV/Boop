#include "context.h"
#include "render.h"

int main() {
	construct_context();
	construct_renderer();
	while(!glfwWindowShouldClose(window)) {
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

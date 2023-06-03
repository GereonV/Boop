#include <stdio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {
	if(!glfwInit()) {
		puts("glfwInit() failed");
		return 1;
	}
	GLFWwindow * window = glfwCreateWindow(1920, 1080, "Boop", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if(!gladLoadGL(glfwGetProcAddress)) {
		puts("gladLoadGL() failed");
		return 1;
	}
	glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
	while(!glfwWindowShouldClose(window)) {
		// int width, height;
		// glfwGetFramebufferSize(window, &width, &height);
		// glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

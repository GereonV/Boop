#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"

static float const vertices[] = {
	-0.5f, -0.5f,  0.0f,
	 0.5f, -0.5f,  0.0f,
	 0.5f,  0.5f,  0.0f,
	-0.5f,  0.5f,  0.0f,
};

static unsigned char const indicies[] = {
	0, 1, 2, // front bottom right
	0, 3, 2, // front top left
};

int main() {
	if(!glfwInit()) {
		puts("glfwInit() failed");
		return 1;
	}
	atexit(glfwTerminate);
	GLFWwindow * window = glfwCreateWindow(1920, 1080, "Boop", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if(!gladLoadGL(glfwGetProcAddress)) {
		puts("gladLoadGL() failed");
		return 1;
	}
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	GLuint bufs[2];
	glCreateBuffers(2, bufs);
	GLuint vbo = bufs[0], ebo = bufs[1];
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
	glVertexArrayElementBuffer(vao, ebo);
	glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(ebo, sizeof(indicies), indicies, GL_STATIC_DRAW);
	GLuint program = create_shaders();
	glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
	while(!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		glUseProgram(program);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

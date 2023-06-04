#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"

constexpr float vertices[] = {
	// near bottom left
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, //  0 x
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, //  1 y
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //  2 z
	// near bottom right
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //  3 x
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, //  4 y
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //  5 z
	// near top right
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //  6 x
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //  7 y
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //  8 z
	// near top left
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, //  9 x
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 10 y
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // 11 z
	// far bottom left
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 12 x
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 13 y
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 14 z
	// far bottom right
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 15 x
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 16 y
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 17 z
	// far top right
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 18 x
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 19 y
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 20 z
	// far top left
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 21 x
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 22 y
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 23 z
};

constexpr unsigned char indicies[] = {
	// near
	 2,  5,  8,
	 2,  8, 11,
	// far
	14, 20, 17,
	14, 23, 20,
	// left
	12,  0,  9,
	12,  9, 21,
	// right
	 3, 15, 18,
	 3, 18,  6,
	// top
	10,  7, 19,
	10, 19, 22,
	// bottom
	13, 16,  4,
	13,  4,  1,
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
	GLuint vao; glCreateVertexArrays(1, &vao);
	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	glEnableVertexArrayAttrib(vao, 1);
	glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, false, 3 * sizeof(float));
	glVertexArrayAttribBinding(vao, 1, 0);
	GLuint vbo; glGenBuffers(1, &vbo);
	GLuint ebo; glCreateBuffers(1, &ebo);
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 6 * sizeof(float));
	glVertexArrayElementBuffer(vao, ebo);
	glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(ebo, sizeof(indicies), indicies, GL_STATIC_DRAW);
	GLuint program = create_shaders();
	glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glfwSwapInterval(0);
	while(!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double time = glfwGetTime();
		glBindVertexArray(vao);
		glUseProgram(program);
		glUniform1f(0, (float) width / (float) height);
		glUniform1f(1, (float) time);
		glDrawElements(GL_TRIANGLES, sizeof(indicies), GL_UNSIGNED_BYTE, nullptr);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

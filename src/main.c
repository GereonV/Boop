#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"

static float const vertices[] = {
	-0.5f, -0.5f,  0.5f, // 0 near bottom left
	 0.5f, -0.5f,  0.5f, // 1 near bottom right
	 0.5f,  0.5f,  0.5f, // 2 near top    right
	-0.5f,  0.5f,  0.5f, // 3 near top    left
	-0.5f, -0.5f, -0.5f, // 4 far  bottom left
	 0.5f, -0.5f, -0.5f, // 5 far  bottom right
	 0.5f,  0.5f, -0.5f, // 6 far  top    right
	-0.5f,  0.5f, -0.5f, // 7 far  top    left
};

// 0 1 3 (near   bottom left)
// 3 1 2 (near   top    right)
// 3 2 6 (top    near   right)
// 6 2 1 (right  near   top)
// 6 1 5 (right  far    bottom)
// 5 1 0 (bottom near   right)
// 5 0 4 (bottom far    left)
// 4 0 3 (left   near   bottom)
// 4 3 7 (left   far    top)
// 7 3 6 (top    far    left)
// 7 6 4 (far    top    left)
// 4 6 5 (far    bottom right)
static unsigned char const indicies[] = {
	0, 1, 3, 2, 6, 1, 5, 0, 4, 3, 7, 6, 4, 5
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
	GLuint vbo; glGenBuffers(1, &vbo);
	GLuint ebo; glCreateBuffers(1, &ebo);
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
	glVertexArrayElementBuffer(vao, ebo);
	glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(ebo, sizeof(indicies), indicies, GL_STATIC_DRAW);
	GLuint program = create_shaders();
	glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
		glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_BYTE, nullptr);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

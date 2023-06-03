#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shader.h"

static float const vertices[] = {
	-0.5f, -0.5f,  0.5f, // front bottom left
	 0.5f, -0.5f,  0.5f, // front bottom right
	 0.5f,  0.5f,  0.5f, // front top    right
	-0.5f,  0.5f,  0.5f, // front top    left
	-0.5f, -0.5f, -0.5f, // back  bottom left
	 0.5f, -0.5f, -0.5f, // back  bottom right
	 0.5f,  0.5f, -0.5f, // back  top    right
	-0.5f,  0.5f, -0.5f, // back  top    left
};

static unsigned char const indicies[] = {
	0, 1, 2, // front  bottom right
	0, 3, 2, // front  top    left
	4, 5, 6, // back   bottom right
	4, 7, 6, // back   top    left
	1, 5, 6, // right  bottom far
	1, 2, 6, // right  top    near
	4, 0, 3, // left   bottom near
	4, 7, 3, // left   top    far
	3, 2, 6, // top    near   right
	3, 7, 6, // top    far    left
	0, 1, 5, // bottom near   right
	0, 4, 5, // bottom far    left
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
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

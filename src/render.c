#include "render_impl.h"

#define ASPECT_RATIO_UNIFORM_LOCATION 0
#define ANGLE_UNIFORM_LOCATION        1

void render() {
	int width, height;
	double time = glfwGetTime();
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glUseProgram(program);
	glUniform1f(ASPECT_RATIO_UNIFORM_LOCATION, (float) width / (float) height);
	glUniform1f(ANGLE_UNIFORM_LOCATION, (float) time);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	glBindVertexArray(0);
	glUseProgram(0);
}

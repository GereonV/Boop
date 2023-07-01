#include "render_impl.h"
#include "matrix.h"

#define PROJECTION_MATRIX_UNIFORM_LOCATION 0

static struct {
	mat4 model_view_matrix;
	mat3 normal_matrix;
} matrices = {
	{{1.0f}, {[1] = 1.0f}, {[2] = 1.0f}, {[3] = 1.0f}},
	{{1.0f}, {[1] = 1.0f}, {[2] = 1.0f}}
};

void render() {
	calculate_model_view_and_normal_matrix(&matrices.model_view_matrix, &matrices.normal_matrix,
		&(object_t) {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0.0f},
		(vec3) {0.0f, 0.0f, 1.0f});
	int width, height;
	// double time = glfwGetTime();
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glUseProgram(program);
	glNamedBufferSubData(instance_vbo, 0, sizeof(matrices), &matrices);
	glUniformMatrix4fv(PROJECTION_MATRIX_UNIFORM_LOCATION, 1, false, (float *) calculate_projection_matrix((float) width / (float) height));
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr, 1);
	glBindVertexArray(0);
	glUseProgram(0);
	glfwSwapBuffers(window);
}

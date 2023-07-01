#include "render_impl.h"

#define ARRSIZE(a) sizeof(a) / sizeof(a[0])
#define PROJECTION_MATRIX_UNIFORM_LOCATION 0

instance_attributes_t instance_attributes[] = {
	instance_attributes_identity,
	instance_attributes_identity,
};

constexpr object_t objects[] = {
	{{-1.0f, -0.5f,  0.0f}, {1.0f, 1.0f, 1.0f}, 0.0f},
	{{ 2.0f, -0.7f, -4.0f}, {2.0f, 1.0f, 5.0f}, 1.0f},
};

static_assert(ARRSIZE(instance_attributes) == ARRSIZE(objects));

void render() {
	double time = glfwGetTime();
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	for(int i = 0; i < ARRSIZE(instance_attributes); ++i)
		calculate_model_view_and_normal_matrix(&instance_attributes[i].model_view_matrix, &instance_attributes[i].normal_matrix,
			&objects[i],
			(vec3) {0.0f, 0.0f, 3.0f});
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glUseProgram(program);
	glNamedBufferSubData(instance_vbo, 0, sizeof(instance_attributes), instance_attributes);
	glUniformMatrix4fv(PROJECTION_MATRIX_UNIFORM_LOCATION, 1, false, (float *) calculate_projection_matrix((float) width / (float) height));
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr, ARRSIZE(instance_attributes));
	glBindVertexArray(0);
	glUseProgram(0);
	glfwSwapBuffers(window);
}

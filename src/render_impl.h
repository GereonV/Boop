#include "render.h"
#include <glad/gl.h>
#include "matrix.h"

extern GLuint program, vao, instance_vbo;

typedef struct {
	mat4 model_view_matrix;
	mat3 normal_matrix;
} instance_attributes_t;
constexpr instance_attributes_t instance_attributes_identity = {
	{{1.0f}, {[1] = 1.0f}, {[2] = 1.0f}, {[3] = 1.0f}},
	{{1.0f}, {[1] = 1.0f}, {[2] = 1.0f}}
};
extern instance_attributes_t instance_attributes[2];

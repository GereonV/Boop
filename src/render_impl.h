#include "render.h"
#include <glad/gl.h>
#include "matrix.h"

#define ARRSIZE(a) sizeof(a) / sizeof(a[0])

extern GLuint program, vao, instance_vbo;

typedef struct {
	mat4 model_view_matrix;
	mat3 normal_matrix;
} instance_attributes_t;
extern instance_attributes_t instance_attributes[2];

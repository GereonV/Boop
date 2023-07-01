#ifndef BOOP_MATRIX_H
#define BOOP_MATRIX_H

// column major
typedef float mat3[3][3];
typedef float mat4[4][4];
typedef struct {
	float x, y, z;
} vec3;

typedef struct {
	vec3 position;
	vec3 scale;
	float z_rotation_radians;
} object_t;

// model_view and normal are assumed to be identities or previous results
void calculate_model_view_and_normal_matrix(mat4 * model_view, mat3 * normal, object_t const * object, vec3 camera_position);
mat4 const * calculate_projection_matrix(float fov);

#endif
#ifndef BOOP_MATRIX_H
#define BOOP_MATRIX_H

// column major
typedef float mat3[3][3];
typedef float mat4[4][4];
constexpr mat3 mat3_identity = {
	{1.0f}, {[1] = 1.0f}, {[2] = 1.0f},
};
constexpr mat4 mat4_identity = {
	{1.0f}, {[1] = 1.0f}, {[2] = 1.0f}, {[3] = 1.0f},
};

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

// x -> -near*x/z
// y -> -near*y/z
// z -> -2/(far-near)*(near+z)-1
//
// [-near     0  0  0][x]   [-near*x]
// [    0 -near  0  0][y] - [-near*y]
// [    0     0 m1 m2][z] - [m1*z+m2]
// [    0     0  1  0][1]   [z]
//
// m1*z+m2=z*(-2/(far-near)*(near+z)-1)
// z has two solutions; we pick -near and -far
// m1*-near+m2=near ∧ m1*-far+m2=-far
// m1=(far+near)/(far-near) ∧ m2=2*far*near/(far-near)
#define NEAR 0.1f
#define FAR  5.0f
constexpr mat4 perspective_projection_matrix = {
	{-NEAR}, {[1] = -NEAR}, {[2] = (FAR + NEAR)/(FAR - NEAR), 1.0f}, {[2] = 2 * FAR * NEAR / (FAR - NEAR)},
};
// TODO FOV

#endif

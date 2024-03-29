#include "matrix.h"

// x -> near/ar*x/-z
// y -> near*y/-z
// z -> -2/(far-near)*(near+z)-1
//
// [near/ar    0  0  0][x]   [near/ar*x]
// [      0 near  0  0][y] - [near*y]
// [      0    0 m1 m2][z] - [m1*z+m2]
// [      0    0 -1  0][1]   [-z]
//
// m1*z+m2=-z*(-2/(far-near)*(near+z)-1)
// z has two solutions; we pick -near and -far
// m1*-near+m2=-near ∧ m1*-far+m2=far
// m1=(far+near)/(near-far) ∧ m2=2*far*near/(near-far)
#define TOP   0.04f // 43.6° vertical fov
#define NEAR  0.1f
#define FAR  15.0f
static mat4 perspective_projection_matrix = {
	{NEAR / TOP}, {[1] = NEAR / TOP}, {[2] = (FAR + NEAR)/(NEAR - FAR), -1.0f}, {[2] = 2 * FAR * NEAR / (NEAR - FAR)},
};

mat4 const * calculate_projection_matrix(float aspect_ratio) {
	perspective_projection_matrix[0][0] = NEAR / TOP / aspect_ratio;
	return &perspective_projection_matrix;
}

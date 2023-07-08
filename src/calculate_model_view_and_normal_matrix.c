#include "matrix.h"
#include <math.h>

#define AT(m, x, y) (*m)[x][y]

void calculate_model_view_and_normal_matrix(mat4 mv[static restrict 1], mat3 n[static restrict 1], object_t const o[static restrict 1], vec3 cp) {
	auto s = sinf(o->z_rotation_radians);
	auto c = cosf(o->z_rotation_radians);
	AT(n, 0, 0) = c; AT(n, 1, 0) = -s;
	AT(n, 0, 1) = s; AT(n, 1, 1) =  c;
	AT(mv, 0, 0) = o->scale.x * c; AT(mv, 1, 0) = -o->scale.y * s; AT(mv, 3, 0) = o->position.x - cp.x;
	AT(mv, 0, 1) = o->scale.y * s; AT(mv, 1, 1) =  o->scale.y * c; AT(mv, 3, 1) = o->position.y - cp.y;
	AT(mv, 2, 2) = o->scale.z;                                     AT(mv, 3, 2) = o->position.z - cp.z;
}

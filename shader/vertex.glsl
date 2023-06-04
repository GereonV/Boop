#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 0) uniform float uAspectRatio;
layout (location = 1) uniform float uAngle;
out float localZ;
out float ndcZ;

void main() {
	float s = sin(uAngle);
	float c = cos(uAngle);
	vec3 pos = inPos.x * vec3(c, 0, -s) +
	           inPos.y * vec3(0, 1,  0) +
	           inPos.z * vec3(s, 0,  c);
	pos.x /= uAspectRatio;
	pos.z *= -1;
	gl_Position = vec4(pos, 1);
	localZ = inPos.z;
	ndcZ = pos.z;
}

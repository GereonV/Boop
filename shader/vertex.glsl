#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 0) uniform float uAspectRatio;
layout (location = 1) uniform float uAngle;

void main() {
	float s = sin(uAngle);
	float c = cos(uAngle);
	vec3 pos = inPos.x * vec3(c, 0, -s) +
	           inPos.y * vec3(0, 1,  0) +
	           inPos.z * vec3(s, 0,  c);
	pos.x /= uAspectRatio;
	gl_Position = vec4(pos, 1);
}

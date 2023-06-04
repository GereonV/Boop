#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 0) uniform float uAspectRatio;
layout (location = 1) uniform float uAngle;
out vec3 color;

void main() {
	float x = gl_InstanceID % 200 / 199.0;
	float y = gl_InstanceID / 200 / 199.0;
	float s = sin(uAngle);
	float c = cos(uAngle);
	vec3 pos = inPos / 100;
	pos = pos.x * vec3(c, 0, -s) +
	      pos.y * vec3(0, 1,  0) +
	      pos.z * vec3(s, 0,  c);
	pos = pos.x * vec3(1,  0, 0) +
	      pos.y * vec3(0,  c, s) +
	      pos.z * vec3(0, -s, c);
	pos.x = pos.x + 2 * (x - 0.5) * uAspectRatio;
	pos.y = pos.y + 2 * (y - 0.5);
	pos.x /= uAspectRatio;
	pos.z *= -1;
	gl_Position = vec4(pos, 1);
	color = inPos + 0.5;
}

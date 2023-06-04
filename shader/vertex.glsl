#version 460 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 0) uniform float uAspectRatio;
layout (location = 1) uniform float uAngle;
out vec3 color;
out vec3 position;
out vec3 normal;

void main() {
	float s = sin(uAngle);
	float c = cos(uAngle);
	vec3 pos = vPosition;
	pos = pos.x * vec3(c, 0, -s) +
	      pos.y * vec3(0, 1,  0) +
	      pos.z * vec3(s, 0,  c);
	pos = pos.x * vec3(1,  0, 0) +
	      pos.y * vec3(0,  c, s) +
	      pos.z * vec3(0, -s, c);
	pos.x /= uAspectRatio;
	pos.z *= -1;
	gl_Position = vec4(pos, 1);
	color = vPosition + 0.5;
	position = pos;
	// position.x *= uAspectRatio;
	normal = vNormal;
	normal = normal.x * vec3(c, 0, -s) +
	         normal.y * vec3(0, 1,  0) +
	         normal.z * vec3(s, 0,  c);
	normal = normal.x * vec3(1,  0, 0) +
	         normal.y * vec3(0,  c, s) +
	         normal.z * vec3(0, -s, c);
	normal.z *= -1;
}

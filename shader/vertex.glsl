#version 460 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in mat4 vModelViewMat;
layout (location = 6) in mat3 vNormalMat;
layout (location = 0) uniform mat4 uProjectionMat;
out vec3 position;
out vec3 normal;
out vec3 color;

void main() {
	vec4 pos = vModelViewMat * vec4(vPosition, 1);
	gl_Position = uProjectionMat * pos;
	position = pos.xyz;
	normal = vNormalMat * vNormal;
	color = vPosition + 0.5;
}

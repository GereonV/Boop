#define FRAGMENT_GLSL \
"#version 460 core\n" \
"\n" \
"out vec4 outColor;\n" \
"\n" \
"void main() {\n" \
"	outColor = vec4(0.2, 1, .4, 1);\n" \
"}\n" \
""
#define VERTEX_GLSL \
"#version 460 core\n" \
"\n" \
"layout (location = 0) in vec3 inPos;\n" \
"layout (location = 0) uniform float uAspectRatio;\n" \
"layout (location = 1) uniform float uAngle;\n" \
"\n" \
"void main() {\n" \
"	float s = sin(uAngle);\n" \
"	float c = cos(uAngle);\n" \
"	vec3 pos = inPos.x * vec3(c, 0, -s) +\n" \
"	           inPos.y * vec3(0, 1,  0) +\n" \
"	           inPos.z * vec3(s, 0,  c);\n" \
"	pos.x /= uAspectRatio;\n" \
"	gl_Position = vec4(pos, 1);\n" \
"}\n" \
""

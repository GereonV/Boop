#define FRAGMENT_GLSL \
"#version 460 core\n" \
"\n" \
"in vec3 color;\n" \
"out vec4 outColor;\n" \
"\n" \
"void main() {\n" \
"	outColor = vec4(color, 1);\n" \
"}\n" \
""
#define VERTEX_GLSL \
"#version 460 core\n" \
"\n" \
"layout (location = 0) in vec3 inPos;\n" \
"layout (location = 0) uniform float uAspectRatio;\n" \
"layout (location = 1) uniform float uAngle;\n" \
"out vec3 color;\n" \
"\n" \
"void main() {\n" \
"	float x = gl_InstanceID % 200 / 199.0;\n" \
"	float y = gl_InstanceID / 200 / 199.0;\n" \
"	float s = sin(uAngle);\n" \
"	float c = cos(uAngle);\n" \
"	vec3 pos = inPos / 100;\n" \
"	pos = pos.x * vec3(c, 0, -s) +\n" \
"	      pos.y * vec3(0, 1,  0) +\n" \
"	      pos.z * vec3(s, 0,  c);\n" \
"	pos = pos.x * vec3(1,  0, 0) +\n" \
"	      pos.y * vec3(0,  c, s) +\n" \
"	      pos.z * vec3(0, -s, c);\n" \
"	pos.x = pos.x + 2 * (x - 0.5) * uAspectRatio;\n" \
"	pos.y = pos.y + 2 * (y - 0.5);\n" \
"	pos.x /= uAspectRatio;\n" \
"	pos.z *= -1;\n" \
"	gl_Position = vec4(pos, 1);\n" \
"	color = inPos + 0.5;\n" \
"}\n" \
""

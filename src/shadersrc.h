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
"\n" \
"void main() {\n" \
"	gl_Position = vec4(inPos, 1);\n" \
"}\n" \
""

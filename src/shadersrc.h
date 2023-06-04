#define FRAGMENT_GLSL \
"#version 460 core\n" \
"\n" \
"in float localZ; // ∈ [0.5, -0.5] (front, back)\n" \
"in float ndcZ;   // ∈ [-1/√2, 0.5) (near, far) (visible)\n" \
"out vec4 outColor;\n" \
"\n" \
"void main() {\n" \
"	vec3 base = mix(vec3(0.4, 0.6, 1), vec3(0.6, 1, 0.4), localZ + 0.5);\n" \
"	vec3 color = mix(base, vec3(0), (ndcZ + 1) / 2);\n" \
"	outColor = vec4(color, 0);\n" \
"}\n" \
""
#define VERTEX_GLSL \
"#version 460 core\n" \
"\n" \
"layout (location = 0) in vec3 inPos;\n" \
"layout (location = 0) uniform float uAspectRatio;\n" \
"layout (location = 1) uniform float uAngle;\n" \
"out float localZ;\n" \
"out float ndcZ;\n" \
"\n" \
"void main() {\n" \
"	float s = sin(uAngle);\n" \
"	float c = cos(uAngle);\n" \
"	vec3 pos = inPos.x * vec3(c, 0, -s) +\n" \
"	           inPos.y * vec3(0, 1,  0) +\n" \
"	           inPos.z * vec3(s, 0,  c);\n" \
"	pos = pos.x * vec3(1,  0, 0) +\n" \
"	      pos.y * vec3(0,  c, s) +\n" \
"	      pos.z * vec3(0, -s, c);\n" \
"	pos.x /= uAspectRatio;\n" \
"	pos.z *= -1;\n" \
"	gl_Position = vec4(pos, 1);\n" \
"	localZ = inPos.z;\n" \
"	ndcZ = pos.z;\n" \
"}\n" \
""

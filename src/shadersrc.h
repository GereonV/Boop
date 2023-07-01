#define FRAGMENT_GLSL \
"#version 460 core\n" \
"\n" \
"in vec3 position;\n" \
"in vec3 normal;\n" \
"in vec3 color;\n" \
"out vec4 fColor;\n" \
"\n" \
"const vec3 lightColor = vec3(1);\n" \
"const float ambientStrength = 0.1;\n" \
"const vec3 lightPos = {1, 1, 1};\n" \
"const float specularBrightness = 0.5;\n" \
"const float shininess = 32;\n" \
"\n" \
"void main() {\n" \
"	float ambient = ambientStrength;\n" \
"\n" \
"	vec3 fragToLight = normalize(lightPos - position);\n" \
"	float diffuseStrength = max(dot(normal, fragToLight), 0);\n" \
"	float diffuse = diffuseStrength;\n" \
"\n" \
"	vec3 fragToCam = -normalize(position);\n" \
"	vec3 reflected = reflect(-fragToLight, normal);\n" \
"	float specStrength = pow(max(dot(reflected, fragToCam), 0), shininess);\n" \
"	float specular = specularBrightness * specStrength;\n" \
"\n" \
"	fColor = vec4((ambient + diffuse + specular) * lightColor * color, 1);\n" \
"	fColor = vec4(color, 1);\n" \
"}\n" \
""
#define VERTEX_GLSL \
"#version 460 core\n" \
"\n" \
"layout (location = 0) in vec3 vPosition;\n" \
"layout (location = 1) in vec3 vNormal;\n" \
"layout (location = 2) in mat4 vModelViewMat;\n" \
"layout (location = 6) in mat3 vNormalMat;\n" \
"layout (location = 0) uniform mat4 uProjectionMat;\n" \
"out vec3 position;\n" \
"out vec3 normal;\n" \
"out vec3 color;\n" \
"\n" \
"void main() {\n" \
"	vec4 pos = vModelViewMat * vec4(vPosition, 1);\n" \
"	gl_Position = uProjectionMat * pos;\n" \
"	position = pos.xyz;\n" \
"	normal = vNormalMat * vNormal;\n" \
"	color = vPosition + 0.5;\n" \
"}\n" \
""

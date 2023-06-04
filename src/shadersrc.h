#define FRAGMENT_GLSL \
"#version 460 core\n" \
"\n" \
"in vec3 color;\n" \
"in vec3 position;\n" \
"in vec3 normal;\n" \
"out vec4 fColor;\n" \
"\n" \
"const vec3 lightColor = vec3(1);\n" \
"const float ambientStrength = 0.1;\n" \
"const vec3 lightPos = {1, 1, -1};\n" \
"const vec3 viewPos = {0, 0, -1};\n" \
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
"	vec3 fragToCam = normalize(viewPos - position);\n" \
"	vec3 reflected = reflect(-fragToLight, normal);\n" \
"	float specStrength = pow(max(dot(reflected, fragToCam), 0), shininess);\n" \
"	float specular = specularBrightness * specStrength;\n" \
"\n" \
"	fColor = vec4((ambient + diffuse + specular) * lightColor * color, 1);\n" \
"}\n" \
""
#define VERTEX_GLSL \
"#version 460 core\n" \
"\n" \
"layout (location = 0) in vec3 vPosition;\n" \
"layout (location = 1) in vec3 vNormal;\n" \
"layout (location = 0) uniform float uAspectRatio;\n" \
"layout (location = 1) uniform float uAngle;\n" \
"out vec3 color;\n" \
"out vec3 position;\n" \
"out vec3 normal;\n" \
"\n" \
"void main() {\n" \
"	float s = sin(uAngle);\n" \
"	float c = cos(uAngle);\n" \
"	vec3 pos = vPosition;\n" \
"	pos = pos.x * vec3(c, 0, -s) +\n" \
"	      pos.y * vec3(0, 1,  0) +\n" \
"	      pos.z * vec3(s, 0,  c);\n" \
"	pos = pos.x * vec3(1,  0, 0) +\n" \
"	      pos.y * vec3(0,  c, s) +\n" \
"	      pos.z * vec3(0, -s, c);\n" \
"	pos.x /= uAspectRatio;\n" \
"	pos.z *= -1;\n" \
"	gl_Position = vec4(pos, 1);\n" \
"	color = vPosition + 0.5;\n" \
"	position = pos;\n" \
"	// position.x *= uAspectRatio;\n" \
"	normal = vNormal;\n" \
"	normal = normal.x * vec3(c, 0, -s) +\n" \
"	         normal.y * vec3(0, 1,  0) +\n" \
"	         normal.z * vec3(s, 0,  c);\n" \
"	normal = normal.x * vec3(1,  0, 0) +\n" \
"	         normal.y * vec3(0,  c, s) +\n" \
"	         normal.z * vec3(0, -s, c);\n" \
"	normal.z *= -1;\n" \
"}\n" \
""

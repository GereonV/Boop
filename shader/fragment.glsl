#version 460 core

in vec3 position;
in vec3 normal;
in vec3 color;
out vec4 fColor;

const vec3 lightColor = vec3(1);
const float ambientStrength = 0.1;
const vec3 lightPos = {1, 1, 1};
const float specularBrightness = 0.5;
const float shininess = 32;

void main() {
	float ambient = ambientStrength;

	vec3 fragToLight = normalize(lightPos - position);
	float diffuseStrength = max(dot(normal, fragToLight), 0);
	float diffuse = diffuseStrength;

	vec3 fragToCam = -normalize(position);
	vec3 reflected = reflect(-fragToLight, normal);
	float specStrength = pow(max(dot(reflected, fragToCam), 0), shininess);
	float specular = specularBrightness * specStrength;

	fColor = vec4((ambient + diffuse + specular) * lightColor * color, 1);
}

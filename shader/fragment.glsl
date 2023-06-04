#version 460 core

in float localZ; // ∈ [0.5, -0.5] (front, back)
in float ndcZ;   // ∈ [-1/√2, 0.5) (near, far) (visible)
out vec4 outColor;

void main() {
	vec3 base = mix(vec3(0.4, 0.6, 1), vec3(0.6, 1, 0.4), localZ + 0.5);
	vec3 color = mix(base, vec3(0), (ndcZ + 1) / 2);
	outColor = vec4(color, 0);
}

#include "render_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"

GLuint program, vao;

#define POSITION_ATTRIBUTE_INDEX      0
#define NORMAL_ATTRIBUTE_INDEX        1
#define BINDING_INDEX                 0

typedef void getter_t(GLuint obj, GLenum name, GLint * out);
typedef void info_log_getter_t(GLuint obj, GLsizei buf_size, GLsizei *, char * buf);

static char * get_info_log(GLuint obj, getter_t * getter, info_log_getter_t * info_log_getter) {
	GLint info_log_length; getter(obj, GL_INFO_LOG_LENGTH, &info_log_length);
	char * info_log = malloc((size_t) info_log_length);
	info_log_getter(obj, (GLsizei) info_log_length, nullptr, info_log);
	return info_log;
}

static GLuint construct_shader(GLenum type, char const * source, char const * restrict name) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	GLint success; glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(success)
		return shader;
	char * info_log = get_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
	fprintf(stderr, "Compilation of %s failed:\n%s", name, info_log);
	// no `free()` because `exit()` will be called
	return 0;
}

constexpr float vertices[] = {
	// near bottom left
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, //  0 x
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, //  1 y
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //  2 z
	// near bottom right
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //  3 x
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, //  4 y
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //  5 z
	// near top right
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //  6 x
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //  7 y
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //  8 z
	// near top left
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, //  9 x
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 10 y
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // 11 z
	// far bottom left
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 12 x
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 13 y
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 14 z
	// far bottom right
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 15 x
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 16 y
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 17 z
	// far top right
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 18 x
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 19 y
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 20 z
	// far top left
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 21 x
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 22 y
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 23 z
};

constexpr unsigned char indicies[] = {
	// near
	 2,  5,  8,
	 2,  8, 11,
	// far
	14, 20, 17,
	14, 23, 20,
	// left
	12,  0,  9,
	12,  9, 21,
	// right
	 3, 15, 18,
	 3, 18,  6,
	// top
	10,  7, 19,
	10, 19, 22,
	// bottom
	13, 16,  4,
	13,  4,  1,
};

void construct_renderer() {
	{ // construct shader program
		GLuint vertex = construct_shader(GL_VERTEX_SHADER, vertex_shader_source, "vertex shader");
		GLuint fragment = construct_shader(GL_FRAGMENT_SHADER, fragment_shader_source, "fragment shader");
		if(!vertex || !fragment)
			exit(1);
		program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
		GLint success; glGetProgramiv(program, GL_LINK_STATUS, &success);
		if(!success) {
			char * info_log = get_info_log(program, glGetProgramiv, glGetProgramInfoLog);
			fprintf(stderr, "Linking failed:\n%s", info_log);
			exit(1);
		}
		glDetachShader(program, vertex);
		glDetachShader(program, fragment);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// construct vertex array object
	glCreateVertexArrays(1, &vao);
	glEnableVertexArrayAttrib(vao, POSITION_ATTRIBUTE_INDEX);
	glVertexArrayAttribFormat(vao, POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(vao, POSITION_ATTRIBUTE_INDEX, BINDING_INDEX);
	glEnableVertexArrayAttrib(vao, NORMAL_ATTRIBUTE_INDEX);
	glVertexArrayAttribFormat(vao, NORMAL_ATTRIBUTE_INDEX, 3, GL_FLOAT, false, 3 * sizeof(float));
	glVertexArrayAttribBinding(vao, NORMAL_ATTRIBUTE_INDEX, BINDING_INDEX);
	{ // construct buffer objects
		GLuint vbo; glGenBuffers(1, &vbo);
		GLuint ebo; glCreateBuffers(1, &ebo);
		glVertexArrayVertexBuffer(vao, BINDING_INDEX, vbo, 0, 6 * sizeof(float));
		glVertexArrayElementBuffer(vao, ebo);
		glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glNamedBufferData(ebo, sizeof(indicies), indicies, GL_STATIC_DRAW);
	}
	// change settings
	glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

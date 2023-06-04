#include "shader.h"
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shadersrc.h"

#ifdef _DEBUG
#include <stdio.h>
typedef void getter_t(GLuint obj, GLenum name, GLint * out);
typedef void info_log_getter_t(GLuint obj, GLsizei buf_size, GLsizei *, char * buf);
static char * get_info_log(GLuint obj, getter_t * getter, info_log_getter_t * info_log_getter) {
	GLint info_log_length; getter(obj, GL_INFO_LOG_LENGTH, &info_log_length);
	char * info_log = malloc((size_t) info_log_length);
	info_log_getter(obj, (GLsizei) info_log_length, nullptr, info_log);
	return info_log;
}
#endif

static GLuint create_shader(GLenum type, char const * source, [[maybe_unused]] char const * restrict name) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	GLint success; glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(success)
		return shader;
#ifdef _DEBUG
	char * info_log = get_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
	fprintf(stderr, "Compilation of %s failed:\n%s", name, info_log);
	// no `free()` because `exit()` will be called
#endif
	return 0;
}

GLuint create_shaders() {
	GLuint vertex = create_shader(GL_VERTEX_SHADER, VERTEX_GLSL, "vertex shader");
	GLuint fragment = create_shader(GL_FRAGMENT_SHADER, FRAGMENT_GLSL, "fragment shader");
	if(!vertex || !fragment)
		exit(1);
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	GLint success; glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
#ifdef _DEBUG
		char * info_log = get_info_log(program, glGetProgramiv, glGetProgramInfoLog);
		fprintf(stderr, "Linking failed:\n%s", info_log);
#endif
		exit(1);
	}
	glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return program;
}

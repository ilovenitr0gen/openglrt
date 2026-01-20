#include "Shader.h"

#include <format>
#include <stdexcept>

constexpr unsigned int INFO_LOG_SIZE = 1024;

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
	int success = 0;
	char infoLog[INFO_LOG_SIZE];

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	const char *vertexChars = vertexSource.c_str();
	glShaderSource(vertex, 1, &vertexChars, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, INFO_LOG_SIZE, nullptr, infoLog);
		throw std::runtime_error(
			std::format("Vertex shader failed to compile.\n", infoLog));
	}

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fragmentChars = fragmentSource.c_str();
	glShaderSource(fragment, 1, &fragmentChars, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, INFO_LOG_SIZE, nullptr, infoLog);
		throw std::runtime_error(
			std::format("Fragment shader failed to compile.\n", infoLog));
	}

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, INFO_LOG_SIZE, nullptr, infoLog);
		throw std::runtime_error(
			std::format("Shader program failed to link.\n", infoLog));
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::use() const {
	glUseProgram(id);
}

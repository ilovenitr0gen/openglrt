#include "Shader.hpp"

#include <format>
#include <stdexcept>

constexpr unsigned int INFO_LOG_SIZE = 1024;

Shader::Shader(const ShaderInfo shaderInfo) : id(glCreateProgram()) {
	int success = 0;
	char infoLog[INFO_LOG_SIZE];

	unsigned int vertex = 0;
	unsigned int fragment = 0;
	unsigned int compute = 0;

	if (!shaderInfo.vertexSource.empty()) {
		vertex = glCreateShader(GL_VERTEX_SHADER);
		const char *vertexChars = shaderInfo.vertexSource.c_str();
		glShaderSource(vertex, 1, &vertexChars, nullptr);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (success == 0) {
			glGetShaderInfoLog(vertex, INFO_LOG_SIZE, nullptr, infoLog);
			throw std::runtime_error(
				std::format("Vertex shader failed to compile.\n{}", infoLog));
		}
		glAttachShader(id, vertex);
	}

	if (!shaderInfo.fragmentSource.empty()) {
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		const char *fragmentChars = shaderInfo.fragmentSource.c_str();
		glShaderSource(fragment, 1, &fragmentChars, nullptr);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (success == 0) {
			glGetShaderInfoLog(fragment, INFO_LOG_SIZE, nullptr, infoLog);
			throw std::runtime_error(
				std::format("Fragment shader failed to compile.\n{}", infoLog));
		}
		glAttachShader(id, fragment);
	}

	if (!shaderInfo.computeSource.empty()) {
		compute = glCreateShader(GL_COMPUTE_SHADER);
		const char *computeChars = shaderInfo.computeSource.c_str();
		glShaderSource(compute, 1, &computeChars, nullptr);
		glCompileShader(compute);
		glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
		if (success == 0) {
			glGetShaderInfoLog(compute, INFO_LOG_SIZE, nullptr, infoLog);
			throw std::runtime_error(
				std::format("Compute shader failed to compile.\n{}", infoLog));
		}
		glAttachShader(id, compute);
	}

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(id, INFO_LOG_SIZE, nullptr, infoLog);
		throw std::runtime_error(
			std::format("Shader program failed to link.\n{}", infoLog));
	}

	if (!shaderInfo.vertexSource.empty()) {
		glDeleteShader(vertex);
	}
	if (!shaderInfo.fragmentSource.empty()) {
		glDeleteShader(fragment);
	}
	if (!shaderInfo.computeSource.empty()) {
		glDeleteShader(compute);
	}
}

Shader::~Shader() { glDeleteProgram(id); }

void Shader::use() const { glUseProgram(id); }

void Shader::setVec3(const std::string &name, const glm::vec3 &value) {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::setFloat(const std::string &name, const float &value) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

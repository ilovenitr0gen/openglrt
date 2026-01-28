#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>

struct ShaderInfo {
	std::string vertexSource;
	std::string fragmentSource;
	std::string computeSource;
};

class Shader {
	public:
		Shader(const ShaderInfo shaderInfo);
		~Shader();

		void use() const;

	private:
		unsigned int id;
};

#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
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

		void setVec3(const std::string &name, const glm::vec3 &value);
		void setFloat(const std::string &name, const float &value);
		void setInt(const std::string &name, const int &value);

	private:
		unsigned int id;
};

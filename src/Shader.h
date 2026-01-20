#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>

class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void use() const;

	private:
		unsigned int id;
};

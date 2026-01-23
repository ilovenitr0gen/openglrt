#include <print>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "DisplayWindow.hpp"
#include "Shader.hpp"

constexpr unsigned int WINDOW_WIDTH = 600;
constexpr unsigned int WINDOW_HEIGHT = 400;
constexpr char WINDOW_TITLE[] = "Title";

int main() {
	std::println("Hello!");

	DisplayWindow window;

	const std::string vertexSource =
#include "shaders/shader.vert"
		;

	const std::string fragmentSource =
#include "shaders/shader.frag"
		;

	Shader shader(ShaderInfo{.vertexSource=vertexSource, .fragmentSource=fragmentSource});

	while (!window.shouldClose()) {
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.swapBuffers();
		glfwPollEvents();
	}

	return 0;
}

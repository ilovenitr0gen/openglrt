#include <print>

#include "Raytracer.hpp"
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
	Raytracer raytracer(window);

	while (!window.shouldClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		raytracer.draw(glm::vec3(0), glm::vec3(0));

		window.swapBuffers();
		glfwPollEvents();
	}

	return 0;
}

#include <print>

#include "Camera.hpp"
#include "Raytracer.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "DisplayWindow.hpp"
#include "Shader.hpp"

constexpr unsigned int WINDOW_WIDTH = 600;
constexpr unsigned int WINDOW_HEIGHT = 400;
constexpr char WINDOW_TITLE[] = "Title";

constexpr double CAMERA_SENSITIVITY = 0.005f;

int main() {
	std::println("Hello!");
	
	DisplayWindow window;
	Raytracer raytracer(window);
	Camera camera(window, glm::vec3(0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), CAMERA_SENSITIVITY);

	while (!window.shouldClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		raytracer.draw(camera.position(), camera.direction(), camera.up());

		window.swapBuffers();
		glfwPollEvents();
	}

	return 0;
}

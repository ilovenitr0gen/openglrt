#include "DisplayWindow.hpp"

#include <stdexcept>

DisplayWindow::DisplayWindow() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window =
		glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (window == nullptr) {
		throw std::runtime_error("Window creation failed");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		throw std::runtime_error("GLAD initialization failed");
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSetFramebufferSizeCallback(
		window, [](GLFWwindow *window, const int width, const int height) {
			glViewport(0, 0, width, height);
		});
}

DisplayWindow::~DisplayWindow() { glfwTerminate(); }

bool DisplayWindow::shouldClose() { return glfwWindowShouldClose(window); }

void DisplayWindow::swapBuffers() { glfwSwapBuffers(window); }

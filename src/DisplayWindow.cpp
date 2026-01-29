#include "DisplayWindow.hpp"

#include <iostream>
#include <stdexcept>

DisplayWindow::DisplayWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
							  nullptr, nullptr);

	if (window == nullptr) {
		throw std::runtime_error("Window creation failed");
	}

	glfwMakeContextCurrent(window);
	// glfwSwapInterval(0);

	glfwSetWindowUserPointer(window, this);

	if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) ==
		0) {
		throw std::runtime_error("GLAD initialization failed");
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSetFramebufferSizeCallback(
		window, [](GLFWwindow *window, const int width, const int height) {
			for (auto &callback :
				 static_cast<DisplayWindow *>(glfwGetWindowUserPointer(window))
					 ->framebufferSizeCallbacks) {
				callback(window, width, height);
			}
		});

	registerFramebufferSizeCallback(
		[](GLFWwindow * /*window*/, const int width, const int height) {
			glViewport(0, 0, width, height);
		});

	// This has to be done for OpenGL to render anything for some reason,
	// regardless of if it is needed
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

DisplayWindow::~DisplayWindow() {
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
}

std::list<std::function<void(GLFWwindow *, const int, const int)>>::iterator
DisplayWindow::registerFramebufferSizeCallback(
	std::function<void(GLFWwindow *, const int, const int)> callback) {
	framebufferSizeCallbacks.emplace_back(std::move(callback));
	return --framebufferSizeCallbacks.end();
}

void DisplayWindow::unregisterFramebufferSizeCallback(
	std::list<std::function<void(GLFWwindow *, const int, const int)>>::iterator
		iter) {
	framebufferSizeCallbacks.erase(iter);
}

std::pair<int, int> DisplayWindow::getFramebufferSize() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return {width, height};
}

bool DisplayWindow::shouldClose() { return glfwWindowShouldClose(window) != 0; }

void DisplayWindow::swapBuffers() { glfwSwapBuffers(window); }

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

	glfwSetCursorPosCallback(
		window, [](GLFWwindow *window, double xpos, double ypos) {
			for (auto &callback :
				 static_cast<DisplayWindow *>(glfwGetWindowUserPointer(window))
					 ->cursorPosCallbacks) {
				callback(window, xpos, ypos);
			}
		});

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode,
								  int action, int mods) {
		for (auto &callback :
			 static_cast<DisplayWindow *>(glfwGetWindowUserPointer(window))
				 ->keyCallbacks) {
			callback(window, key, scancode, action, mods);
		}
	});

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// This has to be done for OpenGL to render anything for some reason,
	// regardless of if it is needed
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	auto [width, height] = getFramebufferSize(); 
	glViewport(0, 0, width, height); //manually set
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

std::list<
	std::function<void(GLFWwindow *, const double, const double)>>::iterator
DisplayWindow::registerCursorPosCallback(
	std::function<void(GLFWwindow *, const double, const double)> callback) {
	cursorPosCallbacks.emplace_back(std::move(callback));
	return --cursorPosCallbacks.end();
}

void DisplayWindow::unregisterCursorPosCallback(
	std::list<std::function<void(GLFWwindow *, const double, const double)>>::
		iterator iter) {
	cursorPosCallbacks.erase(iter);
}

std::list<std::function<void(GLFWwindow *, int, int, int, int)>>::iterator
DisplayWindow::registerKeyCallback(
	std::function<void(GLFWwindow *, int, int, int, int)> callback) {
	keyCallbacks.emplace_back(std::move(callback));
	return --keyCallbacks.end();
}

void DisplayWindow::unregisterKeyCallback(
	std::list<std::function<void(GLFWwindow *, int, int, int, int)>>::iterator
		iter) {
	keyCallbacks.erase(iter);
}

std::list<std::function<void()>>::iterator
DisplayWindow::registerTickCallback(std::function<void()> callback) {
	tickCallbacks.emplace_back(std::move(callback));
	return --tickCallbacks.end();
}

void DisplayWindow::unregisterTickCallback(
	std::list<std::function<void()>>::iterator iter) {
	tickCallbacks.erase(iter);
}

std::pair<int, int> DisplayWindow::getFramebufferSize() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return {width, height};
}

bool DisplayWindow::shouldClose() { return glfwWindowShouldClose(window) != 0; }

void DisplayWindow::swapBuffers() {
	glfwSwapBuffers(window);
	double currentTime = glfwGetTime();
	deltaTime_ = currentTime - lastFrame;
	lastFrame = currentTime;

	for (auto &callback : tickCallbacks) {
		callback();
	}
}

double DisplayWindow::deltaTime() const { return deltaTime_; }

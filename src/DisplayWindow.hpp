#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <list>

extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;
extern const char WINDOW_TITLE[];

class DisplayWindow {
  public:
	DisplayWindow();
	~DisplayWindow();

	std::list<std::function<void(GLFWwindow *, const int, const int)>>::iterator
	registerFramebufferSizeCallback(
		std::function<void(GLFWwindow *, const int, const int)> callback);

	void unregisterFramebufferSizeCallback(
		std::list<std::function<void(GLFWwindow *, const int, const int)>>::
			iterator iter);

	std::list<
		std::function<void(GLFWwindow *, const double, const double)>>::iterator
	registerCursorPosCallback(
		std::function<void(GLFWwindow *, const double, const double)> callback);

	void unregisterCursorPosCallback(
		std::list<std::function<void(GLFWwindow *, const double,
									 const double)>>::iterator iter);

	std::list<std::function<void(GLFWwindow *, int, int, int, int)>>::iterator
	registerKeyCallback(
		std::function<void(GLFWwindow *, int, int, int, int)> callback);

	void unregisterKeyCallback(
		std::list<std::function<void(GLFWwindow *, int, int, int, int)>>::
			iterator iter);

	std::list<std::function<void()>>::iterator
	registerTickCallback(std::function<void()> callback);

	void
	unregisterTickCallback(std::list<std::function<void()>>::iterator iter);

	std::pair<int, int> getFramebufferSize();

	bool shouldClose();
	void swapBuffers();
	[[nodiscard]] double deltaTime() const;

  private:
	GLFWwindow *window;
	unsigned int vao = 0;

	double deltaTime_;
	double lastFrame;

	std::list<std::function<void(GLFWwindow *, const int, const int)>>
		framebufferSizeCallbacks;
	std::list<std::function<void(GLFWwindow *, const double, const double)>>
		cursorPosCallbacks;
	std::list<std::function<void(GLFWwindow *, int, int, int, int)>>
		keyCallbacks;
	std::list<std::function<void()>> tickCallbacks;
};

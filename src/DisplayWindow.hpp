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

	std::pair<int, int> getFramebufferSize();

	bool shouldClose();
	void swapBuffers();

  private:
	GLFWwindow *window;
	unsigned int vao = 0;

	std::list<std::function<void(GLFWwindow *, const int, const int)>>
		framebufferSizeCallbacks;
};

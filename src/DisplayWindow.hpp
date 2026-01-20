#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>


extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;
extern const char WINDOW_TITLE[];

class DisplayWindow {
  public:
	DisplayWindow();
	~DisplayWindow();

	bool shouldClose();
	void swapBuffers();
  private:
	GLFWwindow *window;
};

#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdexcept>

extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;
extern const char WINDOW_TITLE[];

class DisplayWindow {
  public:
	DisplayWindow();
	~DisplayWindow();
  private:
	GLFWwindow *window;
};

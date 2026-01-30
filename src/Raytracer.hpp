#pragma once

#include "DisplayWindow.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;

class Raytracer {
  public:
	explicit Raytracer(DisplayWindow &window);

	void draw(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 cameraUp);

	Raytracer(const Raytracer &) = delete;
	Raytracer &operator=(const Raytracer &) = delete;

	~Raytracer();

  private:
	void resetImage(const int width, const int height);

	unsigned int imageOutput = 0;
	Shader displayShader;
	Shader renderShader;
	DisplayWindow &attachedWindow;
};

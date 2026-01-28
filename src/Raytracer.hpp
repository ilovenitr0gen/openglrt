#pragma once

#include "Shader.hpp"
#include <glm/glm.hpp>

class Raytracer {
  public:
	Raytracer();

	void draw(glm::vec3 cameraPos, glm::vec3 cameraDir);

  private:
	unsigned int imageOutput;
	Shader shader;
};

#pragma once

#include "DisplayWindow.hpp"
#include <glm/glm.hpp>

class Camera {
	public:
		Camera(DisplayWindow &window, glm::vec3 position, glm::vec3 direction, glm::vec3 up, double sensitivity);
		glm::vec3 position();
		glm::vec3 direction();
		glm::vec3 up();
		glm::vec3 right();
		
		void rotate(float yaw, float pitch);

	private:
		glm::vec3 position_;
		glm::vec3 direction_;
		glm::vec3 up_;
		glm::vec3 right_;

		float yaw_ = 0;
		float pitch_ = 0;

		double lastX;
		double lastY;

		double sensitivity = 1;

		DisplayWindow &window;
};

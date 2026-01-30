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
		struct InputState {
			bool forward;
			bool left;
			bool back;
			bool right;
		} inputState;

		glm::vec3 position_;
		glm::vec3 direction_;
		glm::vec3 up_;
		glm::vec3 right_;

		float yaw_ = 0;
		float pitch_ = 0;

		double lastX;
		double lastY;

		double sensitivity = 0.5;
		double speed = 5;

		DisplayWindow &window;
};

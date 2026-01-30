#include "Camera.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

Camera::Camera(DisplayWindow &window, glm::vec3 position, glm::vec3 direction,
			   glm::vec3 up, double sensitivity)
	: window(window), position_(position), direction_(direction), up_(up),
	  right_(glm::cross(direction_, up_)), sensitivity(sensitivity) {
	window.registerCursorPosCallback(
		[this](GLFWwindow *window, const double xpos, const double ypos) {
			double xoffset = xpos - lastX;
			double yoffset = lastY - ypos;
			lastX = xpos;
			lastY = ypos;

			this->rotate(xoffset * this->sensitivity,
						 yoffset * this->sensitivity);
		});
	window.registerKeyCallback([this](GLFWwindow *window, int keycode,
									  int scancode, int action, int mods) {
		switch (keycode) {
		case GLFW_KEY_W:
			if (action == GLFW_PRESS) {
				inputState.forward = true;
			} else if (action == GLFW_RELEASE) {
				inputState.forward = false;
			}
			break;

		case GLFW_KEY_A:
			if (action == GLFW_PRESS) {
				inputState.left = true;
			} else if (action == GLFW_RELEASE) {
				inputState.left = false;
			}
			break;

		case GLFW_KEY_S:
			if (action == GLFW_PRESS) {
				inputState.back = true;
			} else if (action == GLFW_RELEASE) {
				inputState.back = false;
			}
			break;

		case GLFW_KEY_D:
			if (action == GLFW_PRESS) {
				inputState.right = true;
			} else if (action == GLFW_RELEASE) {
				inputState.right = false;
			}
			break;
		}
	});
	window.registerTickCallback([this]() {
		if (inputState.forward) {
			position_ += direction_ *
						 static_cast<float>(speed * this->window.deltaTime());
		}
		if (inputState.left) {
			position_ +=
				-right_ * static_cast<float>(speed * this->window.deltaTime());
		}
		if (inputState.back) {
			position_ += -direction_ *
						 static_cast<float>(speed * this->window.deltaTime());
		}
		if (inputState.right) {
			position_ +=
				right_ * static_cast<float>(speed * this->window.deltaTime());
		}
	});
};

glm::vec3 Camera::position() { return position_; }
glm::vec3 Camera::direction() { return direction_; }
glm::vec3 Camera::up() { return up_; }
glm::vec3 Camera::right() { return right_; }

void Camera::rotate(float yaw, float pitch) {
	yaw_ += yaw;
	pitch_ += pitch;

	pitch_ = std::min(pitch_, glm::radians(89.0f));
	pitch_ = std::max(pitch_, glm::radians(-89.0f));

	direction_.x = std::cos(yaw_) * std::cos(pitch_);
	direction_.y = std::sin(pitch_);
	direction_.z = std::sin(yaw_) * std::cos(pitch_);
	direction_ = glm::normalize(direction_);

	right_ = glm::normalize(glm::cross(direction_, glm::vec3(0, 1, 0)));
	up_ = glm::normalize(glm::cross(right_, direction_));
}

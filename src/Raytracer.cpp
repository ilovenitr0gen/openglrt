#include "Raytracer.hpp"

#include <cmath>
#include <iostream>

const std::string vertexSource =
#include "shaders/shader.vert"
	;

const std::string fragmentSource =
#include "shaders/shader.frag"
	;

const std::string computeSource =
#include "shaders/shader.comp"
	;

Raytracer::Raytracer(DisplayWindow &window)
	: displayShader(ShaderInfo{.vertexSource = vertexSource,
							   .fragmentSource = fragmentSource}),
	  renderShader(ShaderInfo{.computeSource = computeSource}),
	  attachedWindow(window) {

	resetImage(WINDOW_WIDTH, WINDOW_HEIGHT);

	window.registerFramebufferSizeCallback(
		[this](GLFWwindow * /*window*/, const int width, const int height) {
			resetImage(width, height);
		});
	window.registerKeyCallback([this](GLFWwindow *window, int keycode,
									  int scancode, int action, int mods) {
		if (keycode == GLFW_KEY_R and action == GLFW_PRESS) {
			frameIndex = 0;
			shouldAccumulate = !shouldAccumulate;
		}
	});
}

void Raytracer::draw(glm::vec3 cameraPos, glm::vec3 cameraDir,
					 glm::vec3 cameraUp) {

	if (frameIndex == 0 and shouldAccumulate) {
		glClearTexImage(imageOutput, 0, GL_RGBA, GL_FLOAT, 0);
	}
	const float fieldOfView = std::acos(0.0f);

	auto [width, height] = attachedWindow.getFramebufferSize();

	// calculate values needed for shader

	glm::vec3 cameraRight = glm::cross(cameraDir, cameraUp);

	float g_x = std::tan(fieldOfView / 2);
	float g_y = g_x * (height - 1) / (width - 1);

	glm::vec3 q_x = ((2 * g_x) / (width - 1)) * cameraRight;
	glm::vec3 q_y = ((2 * g_y) / (height - 1)) * cameraUp;

	glm::vec3 startPixel = cameraDir - g_x * cameraRight - g_y * cameraUp;

	renderShader.use();

	renderShader.setFloat("deltaTime", attachedWindow.deltaTime());

	renderShader.setInt("frameIndex", static_cast<int>(frameIndex));

	renderShader.setVec3("q_x", q_x);
	renderShader.setVec3("q_y", q_y);
	renderShader.setVec3("startPixel", startPixel);

	renderShader.setVec3("cameraPos", cameraPos);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	glDispatchCompute((unsigned int)width, (unsigned int)height, 1);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	displayShader.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageOutput);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	if (shouldAccumulate) {
		++frameIndex;
	}
}

Raytracer::~Raytracer() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &imageOutput);
}

void Raytracer::resetImage(const int width, const int height) {
	if (imageOutput != 0) {
		glActiveTexture(GL_TEXTURE0);
		glDeleteTextures(1, &imageOutput);
	}

	glGenTextures(1, &imageOutput);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageOutput);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA,
				 GL_FLOAT, NULL);

	glBindImageTexture(0, imageOutput, 0, GL_FALSE, 0, GL_READ_WRITE,
					   GL_RGBA32F);
}

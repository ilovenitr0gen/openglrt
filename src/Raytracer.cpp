#include "Raytracer.hpp"

#include <cmath>

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
}

void Raytracer::draw(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 cameraUp) {

	renderShader.use();

	//All these vectors should be normalised
	renderShader.setVec3("cameraPos", cameraPos);
	renderShader.setVec3("cameraDir", cameraDir);
	renderShader.setVec3("cameraUp", cameraUp);
	renderShader.setVec3("cameraRight", glm::cross(cameraDir, cameraUp));
	renderShader.setFloat("fieldOfView", std::acos(0.0f));

	auto [width, height] = attachedWindow.getFramebufferSize();
	glDispatchCompute((unsigned int)width, (unsigned int)height, 1);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	displayShader.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageOutput);

	glDrawArrays(GL_TRIANGLES, 0, 6);
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

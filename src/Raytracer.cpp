#include "Raytracer.hpp"

const std::string vertexSource =
#include "shaders/shader.vert"
	;

const std::string fragmentSource =
#include "shaders/shader.frag"
	;

Raytracer::Raytracer()
	: shader(ShaderInfo{.vertexSource = vertexSource,
						.fragmentSource = fragmentSource}) {}

void Raytracer::draw(glm::vec3 cameraPos, glm::vec3 cameraDir) {
	shader.use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

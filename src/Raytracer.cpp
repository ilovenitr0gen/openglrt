#include "Raytracer.hpp"

const std::string vertexSource =
#include "shaders/shader.vert"
	;

const std::string fragmentSource =
#include "shaders/shader.frag"
	;

const std::string computeSource =
#include "shaders/shader.comp"
	;

Raytracer::Raytracer()
	: displayShader(ShaderInfo{.vertexSource = vertexSource,
							   .fragmentSource = fragmentSource}),
	  renderShader(ShaderInfo{.computeSource = computeSource}) {
		 
	  }

void Raytracer::draw(glm::vec3 cameraPos, glm::vec3 cameraDir) {

	displayShader.use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

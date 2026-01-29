R"(
#version 460 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex;

void main() {
	
	FragColor = vec4(texture(tex, texCoord).rgb, 1.0f);
}
)"

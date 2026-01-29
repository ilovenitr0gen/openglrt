R"(
#version 460 core

const float vertices[] = {
	-1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, -1.0f,
	-1.0f, -1.0f
};

const float texCoords[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f
};

out vec2 texCoord;

void main() {
	gl_Position = vec4(vertices[gl_VertexID*2], vertices[gl_VertexID*2 + 1], 0.0f, 1);
	texCoord = vec2(texCoords[gl_VertexID*2], texCoords[gl_VertexID*2 + 1]);
}
)"

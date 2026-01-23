R"(
#version 460 core

const float vertices[] = {
	-1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f
};

void main() {
	gl_Position = vec4(vertices[gl_VertexID*3], vertices[gl_VertexID*3 + 1], vertices[gl_VertexID*3 + 2], 1);
}
)"

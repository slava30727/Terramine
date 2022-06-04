#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 a_TexCoord;

void main() {
	a_TexCoord = vertex.zw;
	gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
}
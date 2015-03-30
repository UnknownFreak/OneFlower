#version 430

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texCoord;

out vec2 vertex_texCoord0;

void main () {
	vertex_texCoord0 = vertex_texCoord;
	gl_Position = vec4 (vertex_position, 1.0);
}
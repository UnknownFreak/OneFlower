#version 430

in vec2 vertex_texCoord0;

uniform sampler2D diffuse;
uniform sampler2D lightMap;

out vec4 fragment_color;

void main () {
	vec4 diffuse_color = texture(diffuse, vertex_texCoord0);
	vec4 light_color = texture(lightMap, vertex_texCoord0);
	fragment_color = diffuse_color * (light_color + 0.5f);
	//fragment_color = light_color;
}
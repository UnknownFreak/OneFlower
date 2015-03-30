#version 430

in vec2 vertex_texCoord0;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D worldPos;

layout(location = 0) out vec3 lightBuffer;

vec3 point = vec3(0.0f, 0.0f, 0.0f);

void main () {
	vec4 diffuse_color = texture(diffuse, vertex_texCoord0);
	vec4 normal_color = texture(normal, vertex_texCoord0);
	vec4 world_color = texture(worldPos, vertex_texCoord0);
	
	if(distance(world_color.xyz, point) < 2)
	{
		lightBuffer = vec3(1.0f);
	}
	else
	{
		lightBuffer = vec3(0.0f);
	}
}
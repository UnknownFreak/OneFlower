#version 430
in vec3 color;
//in vec3 normal;
in vec3 worldPos;

//out vec4 fragment_color;

layout (location = 0) out vec3 diffuseOut; 
//layout (location = 1) out vec3 normalOut; 
layout (location = 2) out vec3 worldOut; 

void main ()
{
	diffuseOut = color;
	//normalOut = normalize(normal);
	worldOut = worldPos;
}
#version 430
layout (triangles) in;
layout (line_strip) out;
layout (max_vertices = 3) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 colorG[];
in vec3 worldPosG[];

out vec3 color;
//out vec3 normal;
out vec3 worldPos;

void main () {
	vec4 p1 = model * gl_in[1].gl_Position;
	vec4 p2 = model * gl_in[2].gl_Position;
	vec4 p0 = model * gl_in[0].gl_Position;
	
	//normal = normalize (cross( vec3(p1.xyz - p0.xyz ), vec3(  p2.xyz - p0.xyz ) ) );

		for( int i = 0; i < 3; i++ )
		{
			gl_Position =  projection * view * model * gl_in[i].gl_Position;
			color = colorG[i];
			worldPos = (model * vec4(worldPosG[i], 1.0f)).xyz;
			EmitVertex();
		}
		EndPrimitive();
}
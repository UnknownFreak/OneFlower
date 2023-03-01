#version 450

layout (location = 0) in vec3 vertPos;

layout (location = 0) out vec4 worldPos;
layout (location = 1) out vec3 v_normal;
layout (location = 2) out vec4 v_eye;

uniform layout( push_constant) Camera
{
    mat4 model;
    mat4 view;
    mat4 projection;
    vec4 eye;
} cam;

void main() 
{
    //worldPos = cam.view * cam.model * vec4(vertPos, 1.0);
    //gl_Position = cam.projection * worldPos;
    worldPos =  cam.model * vec4(vertPos, 1.0);
    gl_Position = cam.projection * cam.view * worldPos;
    
    //v_normal = (transpose(inverse(cam.view * cam.model)) * vec4(1.0, 0.0, 0.0 0.0)).xyz;
    v_normal = (cam.model * vec4(1.0, 0.0, 0.0, 0.0)).xyz;
    v_eye = cam.eye;

}
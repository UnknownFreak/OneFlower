#version 450

layout(location = 0) in vec4 worldPos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec4 v_eye;

layout(location = 0) out vec4 fragColor;

uniform layout( push_constant) Color
{
    layout(offset = 208) vec4 color;
} col;

void main()
{

    fragColor = vec4(col.color.rgb, 1.0);
}
#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColors;

out vec4 color;

uniform mat4 MVP;

void main(void)
{
    vec4 positionH = vec4(vertexPosition,1);
    gl_Position = MVP * positionH;
    color = vec4(vertexColors, 1);
}

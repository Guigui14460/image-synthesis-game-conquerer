#version 410

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec3 vertexColor;

out vec3 color;

void main()
{
    vec4 positionH = vec4(vertexPosition, 0, 1);
    gl_Position =  positionH;
    color = vertexColor;
}

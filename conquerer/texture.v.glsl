#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 uv;
void main(void)
{
    vec4 positionH = M * vec4(vertexPosition,1);
    gl_Position = P * V * positionH;
    uv = vertexUV;
}

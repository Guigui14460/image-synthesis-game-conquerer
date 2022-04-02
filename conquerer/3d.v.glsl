#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColors;

out vec4 color;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(void)
{
<<<<<<< HEAD
    vec4 positionH = vec4(vertexPosition,1);
=======
    vec4 positionH = vec4(vertexPosition, 1);
>>>>>>> 76756a395e3f6928abbc77ab9f71bd0850d401ab
    gl_Position = P * V * M * positionH;
    color = vec4(vertexColors, 1);
}

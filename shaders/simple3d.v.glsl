#version 410
/** @note PA2: In this shader you should change the first attribute to be 3d instead of 2d.
 * Then (in part 3) you shall add a uniform MVP matrix and use it in the standard way.
 */

// ins (inputs)
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColors;
// outs
out vec4 color;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
    vec4 positionH = vec4(vertexPosition,1);
    gl_Position = P * V * M * positionH;
    color = vec4(vertexColors, 1);
}

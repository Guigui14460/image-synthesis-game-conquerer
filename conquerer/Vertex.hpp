#ifndef VERTEX_HEADER_H_
#define VERTEX_HEADER_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};

#endif // !VERTEX_HEADER_H_

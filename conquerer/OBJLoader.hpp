#ifndef OBJLOADER_HEADER_H_
#define OBJLOADER_HEADER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include <GLEW/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vertex.h"

static std::vector<Vertex> loadOBJ(const char* filename) {
	std::vector<glm::fvec3> vertexPositions;
	std::vector<glm::fvec2> vertexTexcoords;
	std::vector<glm::fvec3> vertexNormals;

	std::vector<GLint> vertexPositionsIndices;
	std::vector<GLint> vertexTexcoordsIndices;
	std::vector<GLint> vertexNormalsIndices;

	std::vector<Vertex> vertices;

	std::ifstream file(filename);
	if (!file) {
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	glm::vec3 tmpVec3;
	glm::vec2 tmpVec2;
	GLint tmpGLint;
	while (std::getline(file, line)) {
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#") {

		}
		else if (prefix == "o") {

		}
		else if (prefix == "use_mtl") {

		}
		else if (prefix == "v") {
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;
			vertexPositions.push_back(tmpVec3);
			tmpVec3 = glm::vec3();
		}
		else if (prefix == "vt") {
			ss >> tmpVec2.x >> tmpVec2.y;
			vertexTexcoords.push_back(tmpVec2);
			tmpVec2 = glm::vec2();
		}
		else if (prefix == "vn") {
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;
			vertexNormals.push_back(tmpVec3);
			tmpVec3 = glm::vec3();
		}
		else if (prefix == "f") {
			int counter = 0;
			while (ss >> tmpGLint) {
				if (counter == 0)
					vertexPositionsIndices.push_back(tmpGLint);
				else if (counter == 1)
					vertexTexcoordsIndices.push_back(tmpGLint);
				else if (counter == 3)
					vertexNormalsIndices.push_back(tmpGLint);

				if (ss.peek() == '/') {
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ') {
					counter = 0;
					ss.ignore(1, ' ');
				}
			}
		}
		else {}
	}


	std::cout << "Positions indices : " << vertexPositionsIndices.size() << std::endl;
	std::cout << "Normals indices : " << vertexNormalsIndices.size() << std::endl;
	std::cout << "UVs indices : " << vertexTexcoords.size() << std::endl;

	vertices.resize(vertexPositionsIndices.size(), Vertex());
	for (size_t i = 0; i < vertices.size(); i++) {
		vertices[i].position = vertexPositions[vertexPositionsIndices[i] - 1];
		if (vertexTexcoordsIndices.size() <= i) {
			vertices[i].texcoord = glm::vec2(1.f);
		}
		else {
			vertices[i].texcoord = vertexTexcoords[vertexTexcoordsIndices[i] - 1];
		}
		if (vertexNormalsIndices.size() <= i) {
			vertices[i].normal = glm::vec3(1.f);
		}
		else {
			vertices[i].normal = vertexNormals[vertexNormalsIndices[i] - 1];
		}
		vertices[i].color = glm::vec3(1.f);
	}

	return vertices;
}

#endif // !OBJLOADER_HEADER_H_

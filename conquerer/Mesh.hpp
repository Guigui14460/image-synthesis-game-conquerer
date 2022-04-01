#ifndef MESH_HEADER_H_
#define MESH_HEADER_H_

#include <iostream>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "Vertex.hpp"
#include "Primitives.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"

class Mesh
{
private:
	unsigned numberOfVertices, numberOfIndices;
	Vertex* vertices;
	GLuint* indices;

	GLuint vao, vbo, ebo;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	void initVAO();
	void updateModelMatrix();
	void updateUniforms(Shader* shader);

public:
	Mesh(Vertex* vertexArray, const unsigned& numberOfVertices,
		GLuint* indicesArray, const unsigned& numberOfIndices,
		glm::vec3 position = glm::vec3(0.f), glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
	Mesh(Primitive& primitive, glm::vec3 position = glm::vec3(0.f),
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
	Mesh(const Mesh& obj);
	~Mesh();

	inline glm::vec3 getPosition() const {
		return this->position;
	};
	inline glm::vec3 getOrigin() const {
		return this->origin;
	};
	inline glm::vec3 getRotation() const {
		return this->rotation;
	};
	inline glm::vec3 getScale() const {
		return this->scale;
	};

	inline void setPosition(const glm::vec3& position) {
		this->position = position;
	};
	inline void setOrigin(const glm::vec3& origin) {
		this->origin = origin;
	};
	inline void setRotation(const glm::vec3& rotation) {
		this->rotation = rotation;
	};
	inline void setScale(const glm::vec3& scale) {
		this->scale = scale;
	};

	void Delete();
	void update();
	void move(const glm::vec3& position);
	void rotate(const glm::vec3& rotation);
	void zoom(const glm::vec3& scale);
	void render(Shader* shader);
};

#endif // !MESH_HEADER_H_

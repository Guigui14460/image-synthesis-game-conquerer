#include "Mesh.hpp"

Mesh::Mesh(Vertex* vertexArray, const unsigned& numberOfVertices,
	GLuint* indicesArray, const unsigned& numberOfIndices,
	glm::vec3 position, glm::vec3 origin, 
	glm::vec3 rotation, glm::vec3 scale) {
	this->position = position;
	this->origin = origin;
	this->rotation = rotation;
	this->scale = scale;

	this->numberOfVertices = numberOfVertices;
	this->vertices = new Vertex[this->numberOfVertices];
	for (size_t i = 0; i < this->numberOfVertices; i++)
	{
		this->vertices[i] = vertexArray[i];
	}
	this->numberOfIndices = numberOfIndices;
	this->indices = new GLuint[this->numberOfIndices];
	for (size_t i = 0; i < this->numberOfIndices; i++)
	{
		this->indices[i] = indicesArray[i];
	}

	this->initVAO();
	this->updateModelMatrix();
}

Mesh::Mesh(Primitive& primitive, glm::vec3 position,
		glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale) {
	this->position = position;
	this->origin = origin;
	this->rotation = rotation;
	this->scale = scale;

	this->numberOfVertices = primitive.getNumberOfVertices();
	this->vertices = new Vertex[this->numberOfVertices];
	for (size_t i = 0; i < this->numberOfVertices; i++)
	{
		this->vertices[i] = primitive.getVertices()[i];
	}
	this->numberOfIndices = primitive.getNumberOfIndices();
	this->indices = new GLuint[this->numberOfIndices];
	for (size_t i = 0; i < this->numberOfIndices; i++)
	{
		this->indices[i] = primitive.getIndices()[i];
	}

	this->initVAO();
	this->updateModelMatrix();
}

Mesh::Mesh(const Mesh& obj) {
	this->position = obj.position;
	this->origin = obj.origin;
	this->rotation = obj.rotation;
	this->scale = obj.scale;

	this->numberOfVertices = obj.numberOfVertices;
	this->vertices = new Vertex[this->numberOfVertices];
	for (size_t i = 0; i < this->numberOfVertices; i++)
	{
		this->vertices[i] = obj.vertices[i];
	}
	this->numberOfIndices = obj.numberOfIndices;
	this->indices = new GLuint[this->numberOfIndices];
	for (size_t i = 0; i < this->numberOfIndices; i++)
	{
		this->indices[i] = obj.indices[i];
	}

	this->initVAO();
	this->updateModelMatrix();
}


Mesh::~Mesh() {
	this->Delete();
}

void Mesh::Delete() {
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vbo);
	if (this->numberOfIndices > 0)
		glDeleteBuffers(1, &this->ebo);

	delete[] this->vertices;
	delete[] this->indices;
}

void Mesh::initVAO() {
	glCreateVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	// VBO
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->numberOfVertices * sizeof(Vertex), this->vertices, GL_STATIC_DRAW);

	// EBO
	if (this->numberOfIndices > 0) {
		glGenBuffers(1, &this->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numberOfIndices * sizeof(GLuint), this->indices, GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (this->numberOfIndices > 0)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::updateUniforms(Shader* shader) {
	shader->setUniformMat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::updateModelMatrix() {
	this->ModelMatrix = glm::mat4(1.f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

void Mesh::update() {

}

void Mesh::move(const glm::vec3& position) {
	this->position += position;
}

void Mesh::rotate(const glm::vec3& rotation) {
	this->rotation += rotation;
}
void Mesh::zoom(const glm::vec3& scale) {
	this->scale += scale;
}

void Mesh::render(Shader* shader) {
	this->updateModelMatrix();
	this->updateUniforms(shader);

	shader->activate();
	glBindVertexArray(this->vao);
	if (this->numberOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->numberOfVertices);
	else
		glDrawElements(GL_TRIANGLES, this->numberOfIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	shader->deactivate();
}

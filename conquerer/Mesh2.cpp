#include "Mesh.hpp"
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(std::shared_ptr<VAO> vao, glm::vec3 position, glm::vec3 origin, glm::vec3 rotate, glm::vec3 scale)
    : m_vao(vao), m_position(position), m_origin(origin),
      m_rotation(rotate), m_scale(scale), m_modelMatrix(1) {}

void Mesh::move(const glm::vec3& position){
    this->m_position += position;
}

void Mesh::rotate(const glm::vec3 &rotation){
    this->m_rotation += rotation;
}

void Mesh::zoom(const glm::vec3 &scale){
    this->m_scale += scale;
}

void Mesh::updateModelMatrix() {
    this->m_modelMatrix = glm::mat4(1.f);
    this->m_modelMatrix = glm::translate(this->m_modelMatrix, this->m_origin);
    this->m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(this->m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(this->m_rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(this->m_rotation.y), glm::vec3(0.f, 0.f, 1.f));
    this->m_modelMatrix = glm::translate(this->m_modelMatrix, this->m_position - this->m_origin);
    this->m_modelMatrix = glm::scale(this->m_modelMatrix, this->m_scale);
}

void Mesh::update(float /* deltaTime */){}

void Mesh::updateProgram(Program &prog, const glm::mat4 &projViewMatrix) {
    this->updateModelMatrix();
    prog.setUniform("MVP", projViewMatrix * this->m_modelMatrix);
}

void Mesh::render(Program& program, const glm::mat4& projViewMatrix, GLenum mode) {
    this->updateProgram(program, projViewMatrix);
    this->m_vao->draw(mode);
}

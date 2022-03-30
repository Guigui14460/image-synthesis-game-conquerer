#include "PlanetObject.hpp"
#include "BasicObjects.hpp"
#include "Mesh.hpp"

PlanetObject::PlanetObject(const glm::vec3 position, const float health, const glm::vec3 color, const float radius)
    : AbstractGameObject(position, 0, 0, CollisionShapes::SPHERE, health, glm::vec3(SIZE_DEFAULT), radius)
{
    std::shared_ptr<VAO> vao = BasicObjects::makeSphere(40, 40, color, radius);
    this->m_mesh = std::make_shared<Mesh>(vao, position, position);
}

void PlanetObject::draw(const glm::mat4& projViewMatrix, GLenum mode) {
//    this->m_mesh->updateProgram(*m_program, projViewMatrix);
    this->m_mesh->render(mode);
}

void PlanetObject::update(float deltaTime) {}

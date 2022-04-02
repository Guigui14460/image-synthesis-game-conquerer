#include "PlanetObject.hpp"
#include "BasicObjects.hpp"
#include "Mesh.hpp"

PlanetObject::PlanetObject(const glm::vec3 position, const float health, const glm::vec3 color, const float radius)
    : AbstractGameObject(position, 0, 0, CollisionShapes::SPHERE, health, glm::vec3(SIZE_DEFAULT), radius),
      m_program(new Program("conquerer/3d.v.glsl", "conquerer/3d.f.glsl")) {
    std::shared_ptr<VAO> vao = BasicObjects::makeSphere(40, 40, color, radius);
    this->m_mesh = std::make_shared<Mesh>(vao, position, position);
}

void PlanetObject::draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode) {
    this->m_program->bind();
    this->m_mesh->render(*this->m_program.get(), view, projection, mode);
    this->m_program->unbind();
}

void PlanetObject::update(float deltaTime) {}

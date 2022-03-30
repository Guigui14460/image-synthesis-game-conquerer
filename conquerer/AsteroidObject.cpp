#include "AsteroidObject.hpp"

AsteroidObject::AsteroidObject(asteroid_t asteroidType, const glm::vec3 position, const float health, const glm::vec3 sizes)
    : AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, health, sizes), m_asteroidType(asteroidType)
{}

void AsteroidObject::draw(const glm::mat4& projViewMatrix, GLenum mode) {
//    this->m_mesh->updateProgram(*m_program, projViewMatrix);
    this->m_mesh->render(mode);

    // TODO: texture managing, etc
}

void AsteroidObject::update(float deltaTime) {}

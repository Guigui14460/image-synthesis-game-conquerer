#include "AsteroidObject.hpp"

AsteroidObject::AsteroidObject(asteroid_t asteroidType, const glm::vec3 position, const float health, const glm::vec3 sizes)
    : AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, health, sizes), m_asteroidType(asteroidType)
{}

void AsteroidObject::draw(GLenum mode) {
    this->m_mesh->render(mode);

    // TODO: gérer les textures, etc
}

void AsteroidObject::update() {}

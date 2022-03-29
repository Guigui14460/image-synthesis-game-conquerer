#include "ProjectileObject.hpp"

ProjectileObject::ProjectileObject(projectile_t projectileType, const glm::vec3 position, const float health, const glm::vec3 sizes)
    : AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, health, sizes), m_projectileType(projectileType)
{}

void ProjectileObject::draw(const glm::mat4& projViewMatrix, GLenum mode) {
//    this->m_mesh->updateProgram(*m_program, projViewMatrix);
    this->m_mesh->render(mode);

    // TODO: gérer les textures, etc
}

void ProjectileObject::update() {}

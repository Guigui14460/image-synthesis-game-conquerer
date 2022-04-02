#include "ProjectileObject.hpp"

ProjectileObject::ProjectileObject(projectile_t projectileType, const glm::vec3 position, const glm::vec3 orientation, const float health, const glm::vec3 sizes)
    : AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, health, sizes), m_projectileType(projectileType), m_orientation(orientation)
{}

<<<<<<< HEAD
void ProjectileObject::draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode) {
//    this->m_mesh->updateProgram(*m_program, projViewMatrix);
//    this->m_mesh->render(this->m_program, view, projection, mode);
=======
void ProjectileObject::draw(const glm::mat4& projViewMatrix, GLenum mode) {
//    this->m_mesh->updateProgram(*m_program, projViewMatrix);
    this->m_mesh->render(mode);
>>>>>>> origin/game_logic

    // TODO: texture managing, etc
}

void ProjectileObject::update(float deltaTime) {
    this->m_position += deltaTime * this->m_orientation;
}

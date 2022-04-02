#include "ProjectileObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "CollisionShapes.hpp"
#include "utils.hpp"

ProjectileObject::ProjectileObject(projectile_t projectileType, std::shared_ptr<RenderObject> object,
                           std::shared_ptr<Program> program, const float& health,
                           const glm::vec3& position, const glm::vec3& origin,
                           const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3 sizes):
    AbstractGameObject(object, program, health, position, origin, rotation, scale, 0, 0, CollisionShapes::RECTANGLE, sizes),
    m_projectileType(projectileType) {}

std::shared_ptr<ProjectileObject> ProjectileObject::loadObjsProjectile(projectile_t projectileType, std::shared_ptr<Program> program, const float& health,
                                                           const glm::vec3& position, const glm::vec3& origin,
                                                           const glm::vec3& rotation, const glm::vec3& scale)
{
    std::string object = "";
    if(projectileType == OCTOPUS){
        object = absolutename("objConquerer/shoot/octopus/Octobus.obj");
    } else {
        object = absolutename("objConquerer/shoot/shrimp/Shrimp.obj");
    }

    return ProjectileObject::loadObjs(projectileType, object, program, health, position, origin, rotation, scale);
}

std::shared_ptr<ProjectileObject> ProjectileObject::loadObjs(projectile_t projectileType, const std::string & objname, std::shared_ptr<Program> program, const float& health,
                                                     const glm::vec3& position, const glm::vec3& origin,
                                                     const glm::vec3& rotation, const glm::vec3& scale) {
    std::shared_ptr<RenderObject> obj = RenderObject::createWavefrontInstance(objname);

    glm::vec3 sizes(1.f);
    ProjectileObject* objectnew = new ProjectileObject(projectileType, obj, program, health, position, origin, rotation, scale, sizes);
    return std::shared_ptr<ProjectileObject>(objectnew);
}

ProjectileObject::projectile_t ProjectileObject::getProjectileType() {
    return this->m_projectileType;
}

void ProjectileObject::update(float deltaTime) {
    this->m_position += deltaTime * this->m_orientation;
}

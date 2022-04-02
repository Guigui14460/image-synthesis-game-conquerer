#include "PlanetObject.hpp"
#include "BasicObjects.hpp"
#include "Mesh.hpp"

PlanetObject::PlanetObject(const float& health, const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation,
                           const glm::vec3& scale, const glm::vec3& color, const float radius)
    : AbstractGameObject(std::shared_ptr<Mesh>(new Mesh(BasicObjects::makeSphere(40, 40, color, radius))),
                         std::shared_ptr<Program>(new Program("conquerer/3d.v.glsl", "conquerer/3d.f.glsl")),
                         health, position, origin, rotation, scale, 0, 0, CollisionShapes::SPHERE, glm::vec3(-1), radius) {}

void PlanetObject::update(float /* deltaTime */) {}

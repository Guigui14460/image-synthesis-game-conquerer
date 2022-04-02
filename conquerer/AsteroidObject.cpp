#include "AsteroidObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "CollisionShapes.hpp"
#include "utils.hpp"

AsteroidObject::AsteroidObject(asteroid_t asteroidType, std::shared_ptr<RenderObject> object,
                           std::shared_ptr<Program> program, const float& health,
                           const glm::vec3& position, const glm::vec3& origin,
                           const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3 sizes):
    AbstractGameObject(object, program, health, position, origin, rotation, scale, 0, 0, CollisionShapes::RECTANGLE, sizes),
    m_asteroidType(asteroidType) {}

std::shared_ptr<AsteroidObject> AsteroidObject::loadObjsAsteroid(asteroid_t asteroidType, std::shared_ptr<Program> program, const float& health,
                                                           const glm::vec3& position, const glm::vec3& origin,
                                                           const glm::vec3& rotation, const glm::vec3& scale)
{
    std::string object = "";
    if(asteroidType == COD){
        object = absolutename("objConquerer/asteroid/cod/Cod.obj");
    } else if(asteroidType == ALASKA){
        object = absolutename("objConquerer/asteroid/alaska/Alaska_Pollock.obj");
    } else {
        object = absolutename("objConquerer/asteroid/tuna/Tuna.obj");
    }

    return AsteroidObject::loadObjs(asteroidType, object, program, health, position, origin, rotation, scale);
}

std::shared_ptr<AsteroidObject> AsteroidObject::loadObjs(asteroid_t asteroidType, const std::string & objname, std::shared_ptr<Program> program, const float& health,
                                                     const glm::vec3& position, const glm::vec3& origin,
                                                     const glm::vec3& rotation, const glm::vec3& scale) {
    std::shared_ptr<RenderObject> obj = RenderObject::createWavefrontInstance(objname);

    glm::vec3 sizes(1.f);
    AsteroidObject* objectnew = new AsteroidObject(asteroidType, obj, program, health, position, origin, rotation, scale, sizes);
    return std::shared_ptr<AsteroidObject>(objectnew);
}

void AsteroidObject::update(float /* deltaTime */){}

AsteroidObject::asteroid_t AsteroidObject::getAsteroidType() {
    return this->m_asteroidType;
}

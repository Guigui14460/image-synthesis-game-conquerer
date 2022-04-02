#include "PlayerObject.hpp"

#include "CollisionShapes.hpp"
#include "utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

PlayerObject::PlayerObject(player_t typePj, std::shared_ptr<RenderObject> object,
                           std::shared_ptr<Program> program, const float& health,
                           const glm::vec3& position, const glm::vec3& origin,
                           const glm::vec3& rotation, const glm::vec3& scale,
                           const glm::vec3 sizes): AbstractGameObject(object, program, health, position, origin,
                                                                      rotation, scale, 0, 0, CollisionShapes::RECTANGLE, sizes),
                                                                        m_typePj(typePj), m_orientation(0) {}

std::shared_ptr<PlayerObject> PlayerObject::loadObjsPlayer(player_t typePj, std::shared_ptr<Program> program,
                                                           const float& health,const glm::vec3& position,
                                                           const glm::vec3& origin, const glm::vec3& rotation,
                                                           const glm::vec3& scale) {
    std::string object = "";

    glm::vec3 scaleBis = scale;
    scaleBis /= 10;
    if(typePj == PLAYER1) {
        object = absolutename("objConquerer/PJ/dolphin/Dolphin.obj");
    } else if(typePj == PLAYER2) {
        object = absolutename("objConquerer/PJ/shark/Shark.obj");
        scaleBis /= 10;
    } else {
        object = absolutename("objConquerer/asteroid/tuna/Tuna.obj");
    }

    return PlayerObject::loadObjs(typePj, object, program, health, position, origin, rotation, scaleBis);
}

std::shared_ptr<PlayerObject> PlayerObject::loadObjs(player_t typePj, const std::string & objname, std::shared_ptr<Program> program, const float& health,
                                                     const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale) {
    std::shared_ptr<RenderObject> obj = RenderObject::createWavefrontInstance(objname);

    glm::vec3 sizes(1.f);
    PlayerObject* objectnew = new PlayerObject(typePj, obj, program, health, position, origin, rotation, scale, sizes);
    return std::shared_ptr<PlayerObject>(objectnew);
}

void PlayerObject::update(float deltaTime){
    this->move(deltaTime * this->m_orientation);

}

PlayerObject::player_t PlayerObject::getPlayerType() {
    return this->m_typePj;
}

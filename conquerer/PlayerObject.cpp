#include "PlayerObject.hpp"

#include "CollisionShapes.hpp"
#include "utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

PlayerObject::PlayerObject(player_t typePj, std::shared_ptr<RenderObject> object, glm::vec3 position,
                           std::shared_ptr<Program> program, std::shared_ptr<Sampler> colormap):
    AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, glm::vec3(1)),
    m_typePj(typePj), m_object(object), m_program(program), m_colormap(colormap) {}

std::shared_ptr<PlayerObject> PlayerObject::loadObjsPlayer(player_t typePj,  glm::vec3 position, std::shared_ptr<Program> program) {
    std::string object = "";

    if(typePj == PLAYER1) {
        object = absolutename("objConquerer/PJ/dolphin/Dolphin.obj");
    } else if(typePj == PLAYER2) {
        object = absolutename("objConquerer/PJ/shark/Shark.obj");
    } else {
        object = absolutename("objConquerer/asteroid/tuna/Tuna.obj");
    }

    return PlayerObject::loadObjs(typePj, object, position, program);
}

std::shared_ptr<PlayerObject> PlayerObject::loadObjs(player_t typePj, const std::string & objname, glm::vec3 position, std::shared_ptr<Program> program) {
  std::shared_ptr<Sampler> colormap = std::shared_ptr<Sampler>(new Sampler(0));
  colormap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  colormap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(3));
  glm::mat4 scale       = glm::scale(glm::mat4(1.f), glm::vec3(0.5));
  glm::mat4 rotation    = glm::rotate(glm::mat4(1.f), 1.f, {1.f, 0.f, 0.f});
  rotation    = glm::rotate(rotation, 1.f, {0.f, 1.f, 0.f});
  rotation    = glm::rotate(rotation, 1.f, {0.f, 0.f, 1.f});
  std::shared_ptr<RenderObject> obj = RenderObject::createWavefrontInstance(program, objname, translation * rotation * scale);

  PlayerObject* objectnew = new PlayerObject(typePj, obj, position, program, colormap);
  return std::shared_ptr<PlayerObject>(objectnew);

}

void PlayerObject::draw(const glm::mat4 & view, const glm::mat4 & projection){
    this->m_program->bind();
    this->updateProgram(view, projection);

    this->m_colormap->bind();
    this->m_object->draw();
    this->m_colormap->unbind();

    this->m_program->unbind();
}

void PlayerObject::updateProgram(const glm::mat4 & view, const glm::mat4 & projection){
    this->m_program->setUniform("V", view);
    this->m_program->setUniform("P", projection);
}

void PlayerObject::update(float deltaTime) {

}

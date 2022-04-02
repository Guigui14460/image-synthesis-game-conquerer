#include "AsteroidObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "CollisionShapes.hpp"
#include "utils.hpp"

AsteroidObject::AsteroidObject(asteroid_t asteroidType, std::shared_ptr<RenderObject> object,
                           std::shared_ptr<Program> program, std::shared_ptr<Sampler> colormap,
                               const float health,
                           const glm::vec3& position, const glm::vec3& origin,
                           const glm::vec3& rotation, const glm::vec3& scale):
    AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, health, glm::vec3(1)),
    m_asteroidType(asteroidType), m_object(object), m_program(program), m_colormap(colormap) {}

std::shared_ptr<AsteroidObject> AsteroidObject::loadObjsAsteroid(asteroid_t asteroidType, std::shared_ptr<Program> program, const float health,
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

std::shared_ptr<AsteroidObject> AsteroidObject::loadObjs(asteroid_t asteroidType, const std::string & objname, std::shared_ptr<Program> program, const float health,
                                                     const glm::vec3& position, const glm::vec3& origin,
                                                     const glm::vec3& rotation, const glm::vec3& scale) {
  std::shared_ptr<Sampler> colormap = std::shared_ptr<Sampler>(new Sampler(0));
  colormap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  colormap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glm::mat4 translation = glm::translate(glm::mat4(1.f), position);
  glm::mat4 scaleM       = glm::scale(glm::mat4(1.f), scale);
  glm::mat4 rotationM    = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), {1.f, 0.f, 0.f});
  rotationM    = glm::rotate(rotationM, glm::radians(rotation.y), {0.f, 1.f, 0.f});
  rotationM    = glm::rotate(rotationM, glm::radians(rotation.z), {0.f, 0.f, 1.f});
  std::shared_ptr<RenderObject> obj = RenderObject::createWavefrontInstance(program, objname, translation * rotationM * scaleM);

  AsteroidObject* objectnew = new AsteroidObject(asteroidType, obj, program, colormap, health, position, origin, rotation, scale);
  return std::shared_ptr<AsteroidObject>(objectnew);
}

void AsteroidObject::draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum /* mode */){
    m_program->bind();

    this->updateProgram(view, projection);

    m_colormap->bind();
    m_object->draw();
    m_colormap->unbind();

    m_program->unbind();
}

void AsteroidObject::updateProgram(const glm::mat4 & view, const glm::mat4 & projection){
    m_program->setUniform("V", view);
    m_program->setUniform("P", projection);
}

void AsteroidObject::update(float deltaTime){}

AsteroidObject::asteroid_t AsteroidObject::getAsteroidType() {
    return this->m_asteroidType;
}


#include "AbstractGameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.hpp"
#include "RenderObjectConqueror.hpp"

AbstractGameObject::AbstractGameObject(std::shared_ptr<AbstractRenderObject> object, std::shared_ptr<Program> program, const float& health,
                                       const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale,
                                       const float theta, const float phi, const CollisionShapes::shape_t shapeType, const glm::vec3 sizes, const float radius)
    : m_object(object), m_program(program), m_health(health),
        m_position(position), m_origin(origin), m_rotation(rotation), m_scale(scale),
        m_phi(phi), m_theta(theta) {
    switch (shapeType) {
    case CollisionShapes::RECTANGLE:
        this->m_collisionShape = std::shared_ptr<CollisionShapes::RectShape>(new CollisionShapes::RectShape(position, sizes/2.f));
        break;
    case CollisionShapes::POINT:
        this->m_collisionShape = std::shared_ptr<CollisionShapes::PointShape>(new CollisionShapes::PointShape(position));
        break;
    case CollisionShapes::SPHERE:
        this->m_collisionShape = std::shared_ptr<CollisionShapes::SphereShape>(new CollisionShapes::SphereShape(position, radius));
        break;
    default:
        break;
    }

    this->updateModelMatrix();
}

//void AbstractGameObject::rotate(const glm::vec2 &angles) {
//    glm::vec3 rotation;
//    this->m_theta += angles.y;
//    this->m_phi += angles.x;

//    this->m_collisionShape.rotate(rotation);
//    if(this->m_collisionShape.getType() == CollisionShapes::RECTANGLE){
//        rotation.x = glm::cos(glm::radians(this->m_theta)) * glm::cos(glm::radians(this->m_phi));
//        rotation.y = glm::sin(glm::radians(this->m_phi));
//        rotation.z = glm::sin(glm::radians(this->m_theta)) * glm::cos(glm::radians(this->m_phi));
//        rotation = glm::normalize(rotation);

//        CollisionShapes::RectShape& rect = static_cast<CollisionShapes::RectShape&>(this->m_collisionShape);
//        rect.rotate(this->m_position, rotation);
//    }
//}

void AbstractGameObject::updateModelMatrix() {
    this->m_modelMatrix = glm::mat4(1.f);
    this->m_modelMatrix = glm::translate(this->m_modelMatrix, this->m_origin);
    this->m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(this->m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(this->m_rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(this->m_rotation.y), glm::vec3(0.f, 0.f, 1.f));
    this->m_modelMatrix = glm::translate(this->m_modelMatrix, this->m_position - this->m_origin);
    this->m_modelMatrix = glm::scale(this->m_modelMatrix, this->m_scale);
}

void AbstractGameObject::move(const glm::vec3& position){
    this->m_position += position;
    this->m_collisionShape->move(position);
}

void AbstractGameObject::rotate(const glm::vec3 &rotation){
    this->m_rotation += rotation;

    // TODO: refaire la rotation
}

void AbstractGameObject::zoom(const glm::vec3 &scale){
    this->m_scale *= scale;
    this->m_collisionShape->scale(scale);
}

void AbstractGameObject::zoom(const float& value) {
    this->zoom(glm::vec3(value));
}

float AbstractGameObject::removeHealth(const float health){
    this->m_health -= health;
    return this->m_health;
}

bool AbstractGameObject::isCollided(AbstractGameObject &other){
    return CollisionShapes::isCollided(this->m_collisionShape.get(), other.m_collisionShape.get());
}

bool AbstractGameObject::isDestroyed() {
    return this->m_health <= 0.f;
}

void AbstractGameObject::draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode) {
    this->m_object->render(*this->m_program.get(), this->m_modelMatrix, view, projection, mode);
}

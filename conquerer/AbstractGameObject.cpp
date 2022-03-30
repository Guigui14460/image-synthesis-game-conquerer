#include "AbstractGameObject.hpp"

AbstractGameObject::AbstractGameObject(const glm::vec3 position, const float theta, const float phi, const CollisionShapes::shape_t shapeType, const float health, const glm::vec3 sizes, const float radius)
    : m_health(health), m_position(position), m_sizes(sizes), m_phi(phi), m_theta(theta) {
    switch (shapeType) {
    case CollisionShapes::RECTANGLE:
        this->m_collisionShape = CollisionShapes::RectShape(position, sizes/2.f);
        break;
    case CollisionShapes::POINT:
        this->m_collisionShape = CollisionShapes::PointShape(position);
        break;
    case CollisionShapes::SPHERE:
        this->m_collisionShape = CollisionShapes::SphereShape(position, radius);
        break;
    default:
        break;
    }
}

void AbstractGameObject::move(const glm::vec3 &pos) {
    this->m_position += pos;
    this->m_collisionShape.move(pos);
    this->m_mesh->move(pos);
}

void AbstractGameObject::rotate(const glm::vec2 &angles) {
    this->m_theta += angles.y;
    this->m_phi += angles.x;

    glm::vec3 rotation;
    rotation.x = glm::cos(glm::radians(this->m_theta)) * glm::cos(glm::radians(this->m_phi));
    rotation.y = glm::sin(glm::radians(this->m_phi));
    rotation.z = glm::sin(glm::radians(this->m_theta)) * glm::cos(glm::radians(this->m_phi));
    rotation = glm::normalize(rotation);

    this->m_collisionShape.rotate(rotation);
    if(this->m_collisionShape.getType() == CollisionShapes::RECTANGLE){
        CollisionShapes::RectShape& rect = static_cast<CollisionShapes::RectShape&>(this->m_collisionShape);
        rect.rotate(this->m_position, rotation);
    }
    this->m_mesh->rotate(rotation);
}

void AbstractGameObject::scale(const float value) {
    this->m_sizes *= value;
    this->m_collisionShape.scale(value);
    this->m_mesh->zoom(glm::vec3(value));
}

float AbstractGameObject::removeHealth(const float health){
    this->m_health -= health;
    return this->m_health;
}

bool AbstractGameObject::isCollided(AbstractGameObject &other){
    return CollisionShapes::isCollided(this->m_collisionShape, other.m_collisionShape);
}

bool AbstractGameObject::isDestroyed() {
    return this->m_health <= 0.f;
}

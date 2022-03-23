#ifndef __ABSTRACT_GAME_OBJECT_HPP__
#define __ABSTRACT_GAME_OBJECT_HPP__
#include <glm/vec3.hpp>
#include "Mesh.hpp"
#include "CollisionShapes.hpp"

#define RADIUS_DEFAULT -1
#define SIZE_DEFAULT -1

/**
 * @brief The AbstractGameObject class is an abstract class to create all the objects of the Conquerer game.
 */
class AbstractGameObject
{
public:
    AbstractGameObject() = delete;
    AbstractGameObject(const AbstractGameObject& o) = default;

    AbstractGameObject(const glm::vec3 position, const float theta, const float phi, const CollisionShapes::shape_t shapeType, const glm::vec3 sizes = glm::vec3(SIZE_DEFAULT), const float radius = RADIUS_DEFAULT);

    /// Destructor
    virtual ~AbstractGameObject() = default;

    /**
     * @brief Checks the collision between two objects
     * @param other other object to check collision
     * @return boolean representing if a collision is here
     */
    bool isCollided(AbstractGameObject& other);

    /// Checks if the object is destroyed
    bool isDestroyed();

    void move(const glm::vec3& pos);
    void rotate(const glm::vec2& angles);
    void scale(const float value);
    virtual void update() = 0;

    /// Remove some health from the object
    float removeHealth(const float health);

private:
    std::shared_ptr<Mesh> m_mesh; /// The OpenGL object to display
    float m_health; /// Health of the object
    glm::vec3 m_position; /// Position of the object
    glm::vec3 m_sizes; /// Vector representing the sizes of the object (width, height, depth)
    float m_phi, m_theta; /// Direction of the point of view
    CollisionShapes::Shape m_collisionShape; /// Associated collision shape
};

#endif // __ABSTRACT_GAME_OBJECT_HPP__

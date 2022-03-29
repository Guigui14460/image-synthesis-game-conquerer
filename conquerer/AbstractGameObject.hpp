#ifndef __ABSTRACT_GAME_OBJECT_HPP__
#define __ABSTRACT_GAME_OBJECT_HPP__
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glApi.hpp>
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
    /// Default constructor
    AbstractGameObject() = delete;
    /// Copy constructor
    AbstractGameObject(const AbstractGameObject& o) = default;

    /**
     * @brief AbstractGameObject the costructor
     * @param position initial position of the object
     * @param theta
     * @param phi
     * @param shapeType type of shape for the collision shape
     * @param sizes sizes in case of rectangle collision shape
     * @param radius radius in case of sphere collision shape
     */
    AbstractGameObject(const glm::vec3 position, const float theta, const float phi,
                       const CollisionShapes::shape_t shapeType, const float health,
                       const glm::vec3 sizes = glm::vec3(SIZE_DEFAULT),
                       const float radius = RADIUS_DEFAULT);

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

    /**
     * @brief Moves the object to some direction with a vector
     * @param pos position to move the object
     */
    void move(const glm::vec3& pos);

    /**
     * @brief Rotates the object to some direction with a vector
     * @param angles angles to rotate object
     */
    void rotate(const glm::vec2& angles);

    /**
     * @brief Scales the object to value
     * @param value value to scale the object
     */
    void scale(const float value);

    // TODO: faire méthodes comme mesh pour simplifier

    /**
     * @brief Updates the object
     */
    virtual void update() = 0; // TODO: lier à l'orientation de la caméra

    /// Draw meshes to the screen
    virtual void draw(const glm::mat4& projViewMatrix, GLenum mode = GL_TRIANGLES) = 0;

    /// Gets the object health
    float getHealth() { return this->m_health; }

    /// Returns the position of the object
    glm::vec3 getPosition() { return this->m_position; }

    /// Remove some health from the object
    float removeHealth(const float health);

protected:
    std::shared_ptr<Mesh> m_mesh; /// The OpenGL object to display
    float m_health; /// Health of the object
    glm::vec3 m_position; /// Position of the object
    glm::vec3 m_sizes; /// Vector representing the sizes of the object (width, height, depth)
    float m_phi, m_theta; /// Direction of the point of view
    CollisionShapes::Shape m_collisionShape; /// Associated collision shape
};

#endif // __ABSTRACT_GAME_OBJECT_HPP__

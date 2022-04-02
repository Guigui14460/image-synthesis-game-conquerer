#ifndef __ABSTRACT_GAME_OBJECT_HPP__
#define __ABSTRACT_GAME_OBJECT_HPP__
#include <glm/vec3.hpp>
#include "Mesh.hpp"
#include "CollisionShapes.hpp"
#include "AbstractRenderObject.hpp"

#define RADIUS_DEFAULT -1
#define SIZE_DEFAULT -1

/**
 * @brief The AbstractGameObject class is an abstract class to create all the objects of the Conquerer game.
 */
class AbstractGameObject {
public:
    AbstractGameObject() = delete;
    AbstractGameObject(const AbstractGameObject& o) = default;

    AbstractGameObject(std::shared_ptr<AbstractRenderObject> object, std::shared_ptr<Program> program, const float& health,
            const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale,
            const float theta, const float phi, const CollisionShapes::shape_t shapeType, const glm::vec3 sizes = glm::vec3(SIZE_DEFAULT), const float radius = RADIUS_DEFAULT);

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
     * @brief Updates object in function of time
     * @param deltaTime elapsed time between two frames
     */
    virtual void update(float deltaTime) = 0;

    /// Remove some health from the object
    float removeHealth(const float health);

    float getHealth() { return this->m_health; }

    /**
     * @brief draw
     *
     * draw this object
     */
    void draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES);

    /// Gets the position the object
    inline glm::vec3 getPosition() const { return this->m_position; }
    /// Gets the origin the object
    inline glm::vec3 getOrigin() const { return this->m_origin; }
    /// Gets the rotation the object
    inline glm::vec3 getRotation() const { return this->m_rotation; }
    /// Gets the scale the object
    inline glm::vec3 getScale() const { return this->m_scale; }

    /**
     * @brief Sets a new position for the object.
     * @param position new position for the object
     */
    inline void setPosition(const glm::vec3& position) { this->m_position = position; }
    /**
     * @brief Sets a new origin for the object.
     * @param origin new origin for the object
     */
    inline void setOrigin(const glm::vec3& origin) { this->m_origin = origin; }
    /**
     * @brief Sets a new rotation for the object.
     * @param rotation new rotation for the object
     */
    inline void setRotation(const glm::vec3& rotation) { this->m_rotation = rotation; }
    /**
     * @brief Sets a new scale for the object.
     * @param scale new scale for the object
     */
    inline void setScale(const glm::vec3& scale) { this->m_scale = scale; }

    /**
     * @brief Moves the object to a new position (addition of the position).
     * @param position moving value to go
     */
    void move(const glm::vec3& position);

    /**
     * @brief Rotates the object to new angles (addition of the rotation).
     * @param rotation rotating value to go
     */
    void rotate(const glm::vec3& rotation);

    /**
     * @brief Zooms the object to new scale (addition of the scale).
     * @param scale scaling value to go
     */
    void zoom(const glm::vec3& scale);

    /**
     * @brief Zooms the object to new scale (addition of the scale).
     * @param scale scaling value to go
     */
    void zoom(const float& scale);

private:
    /// Updates the model matric of the object.
    void updateModelMatrix();

protected:
    std::shared_ptr<AbstractRenderObject> m_object; /// The OpenGL object to display
    std::shared_ptr<Program> m_program;

    float m_health; /// Health of the object
    glm::vec3 m_position; /// 3D position to display the object
    glm::vec3 m_origin; /// 3D origin position of the object
    glm::vec3 m_rotation; /// 3D rotating value
    glm::vec3 m_scale; /// 3D scaling value
    glm::mat4 m_modelMatrix; /// The world matrix of the object

    float m_phi, m_theta; /// Direction of the point of view
    CollisionShapes::Shape m_collisionShape; /// Associated collision shape
};

#endif // __ABSTRACT_GAME_OBJECT_HPP__

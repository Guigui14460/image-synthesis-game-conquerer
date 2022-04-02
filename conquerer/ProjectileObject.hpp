#ifndef __PROJECTILE_OBJECT_HPP__
#define __PROJECTILE_OBJECT_HPP__
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "AbstractGameObject.hpp"

/**
 * @brief Choice and creation of projectiles in the game's universe
 */
class ProjectileObject: public AbstractGameObject {
public:
    enum projectile_t {OCTOPUS, SHRIMP};

    /// Default constructor
    ProjectileObject() = delete;

    /// Copy constructor
    ProjectileObject(const ProjectileObject& o) = default;

    /// Constructor
    ProjectileObject(projectile_t projectileType, const glm::vec3 position, const glm::vec3 orientation, const float health, const glm::vec3 sizes);

    /// Destructor
    ~ProjectileObject() {}

    /**
     * @brief Updates the object
     */
    void update(float deltaTime) override;

    /// Draw meshes to the screen
<<<<<<< HEAD
    void draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES) override;
=======
    void draw(const glm::mat4& projViewMatrix, GLenum mode = GL_TRIANGLES) override;
>>>>>>> origin/game_logic

private:
    projectile_t m_projectileType;
    glm::vec3 m_orientation;
};

#endif // __PROJECTILE_OBJECT_HPP__

#ifndef __PROJECTILE_OBJECT_HPP__
#define __PROJECTILE_OBJECT_HPP__
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
    ProjectileObject(projectile_t projectileType, const glm::vec3 position, const float health, const glm::vec3 sizes);

    /// Destructor
    ~ProjectileObject() {}

    /**
     * @brief Updates the object
     */
    void update() override;

    /// Draw meshes to the screen
    void draw(const glm::mat4& projViewMatrix, GLenum mode = GL_TRIANGLES) override;

private:
    projectile_t m_projectileType;
};

#endif // __PROJECTILE_OBJECT_HPP__

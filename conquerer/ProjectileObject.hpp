#ifndef __PROJECTILE_OBJECT_HPP__
#define __PROJECTILE_OBJECT_HPP__
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "AbstractGameObject.hpp"
#include "RenderObjectConqueror.hpp"

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
    /// Destructor
    ~ProjectileObject() {}

    /**
     * @brief loadObjsPlayer
     * @param typePj
     * @return object of the player choice because of player's type
     */
    static std::shared_ptr<ProjectileObject> loadObjsProjectile(projectile_t projectileType, std::shared_ptr<Program> program, const float& health,
                                                        const glm::vec3& position, const glm::vec3& origin,
                                                        const glm::vec3& rotation, const glm::vec3& scale);

    /**
     * @brief update
     *
     * update the program
     */
    void update(float deltaTime) override;

    projectile_t getProjectileType();

private:
    /// Constructor
    ProjectileObject(projectile_t projectileType, std::shared_ptr<RenderObject> object,
                     std::shared_ptr<Program> program, const float& health,
                     const glm::vec3& position, const glm::vec3& origin,
                     const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3 sizes);

    /**
     * @brief loadObjs
     * @param objname
     * @return the good object with his different values
     */
    static std::shared_ptr<ProjectileObject> loadObjs(projectile_t projectileType, const std::string & objname,
                  std::shared_ptr<Program> program, const float& health,
                  const glm::vec3& position, const glm::vec3& origin,
                  const glm::vec3& rotation, const glm::vec3& scale);

private:
    projectile_t m_projectileType;
    glm::vec3 m_orientation;
};

#endif // __PROJECTILE_OBJECT_HPP__

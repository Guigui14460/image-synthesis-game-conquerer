#ifndef __PLANET_OBJECT_HPP__
#define __PLANET_OBJECT_HPP__
#include <glm/mat4x4.hpp>
#include "AbstractGameObject.hpp"

/**
 * @brief Choice and creation of planets in the game's universe
 */
class PlanetObject: public AbstractGameObject
{
public:
    /// Default constructor
    PlanetObject() = delete;

    /// Copy constructor
    PlanetObject(const PlanetObject& o) = default;

    /// Constructor
    PlanetObject(const glm::vec3 position, const float health, const glm::vec3 color, const float radius = RADIUS_DEFAULT);

    /// Destructor
    ~PlanetObject() {}

    /**
     * @brief Updates the object
     */
    void update(float deltaTime) override;

    /// Draw meshes to the screen
    void draw(const glm::mat4& projViewMatrix, GLenum mode = GL_TRIANGLES) override;
};

#endif // __PLANET_OBJECT_HPP__

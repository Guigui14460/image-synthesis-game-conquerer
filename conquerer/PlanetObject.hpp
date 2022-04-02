#ifndef __PLANET_OBJECT_HPP__
#define __PLANET_OBJECT_HPP__
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "AbstractGameObject.hpp"
#include "glApi.hpp"
#include "Mesh.hpp"

/**
 * @brief Choice and creation of planets in the game's universe
 */
class PlanetObject: public AbstractGameObject {
public:
    /// Default constructor
    PlanetObject() = delete;

    /// Copy constructor
    PlanetObject(const PlanetObject& o) = default;

    /// Constructor
    PlanetObject(const float& health, const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation,
                 const glm::vec3& scale, const glm::vec3& color, const float radius = RADIUS_DEFAULT);

    /// Destructor
    ~PlanetObject() {}

    /**
     * @brief Updates the object
     */
    void update(float deltaTime) override;
};

#endif // __PLANET_OBJECT_HPP__

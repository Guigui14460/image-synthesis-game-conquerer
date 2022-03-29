#ifndef __ASTEROID_OBJECT_HPP__
#define __ASTEROID_OBJECT_HPP__
#include <glm/mat4x4.hpp>
#include "AbstractGameObject.hpp"

/**
 * @brief Choice and creation of asteroid in the game's universe
 */
class AsteroidObject: public AbstractGameObject {
public:
    enum asteroid_t {ALASKA, COD, TUNA};

    /// Default constructor
    AsteroidObject() = delete;

    /// Copy constructor
    AsteroidObject(const AsteroidObject& o) = default;

    /// Constructor
    AsteroidObject(asteroid_t asteroidType, const glm::vec3 position, const float health, const glm::vec3 sizes);

    /// Destructor
    ~AsteroidObject() {}

    /**
     * @brief Updates the object
     */
    void update() override;

    /// Draw meshes to the screen
    void draw(const glm::mat4& projViewMatrix, GLenum mode = GL_TRIANGLES) override;

private:
    asteroid_t m_asteroidType;
};

#endif // __ASTEROID_OBJECT_HPP__

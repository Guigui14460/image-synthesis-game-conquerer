#ifndef __ASTEROID_OBJECT_HPP__
#define __ASTEROID_OBJECT_HPP__
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "glApi.hpp"
#include "AbstractGameObject.hpp"
#include "RenderObjectConqueror.hpp"

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
    /// Destructor
    ~AsteroidObject() {}

    /**
     * @brief loadObjsPlayer
     * @param typePj
     * @return object of the player choice because of player's type
     */
    static std::shared_ptr<AsteroidObject> loadObjsAsteroid(asteroid_t asteroidType, std::shared_ptr<Program> program, const float health,
                                                        const glm::vec3& position, const glm::vec3& origin,
                                                        const glm::vec3& rotation, const glm::vec3& scale);

    /**
     * @brief draw
     *
     * draw this object
     */
    void draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES);

    /**
     * @brief update
     *
     * update the program
     */
    void update(float deltaTime) override;

    asteroid_t getAsteroidType();

private:
    AsteroidObject(asteroid_t asteroidType, std::shared_ptr<RenderObject> object,
                 std::shared_ptr<Program> program, std::shared_ptr<Sampler> m_colormap,
                 const float health,
                 const glm::vec3& position, const glm::vec3& origin,
                 const glm::vec3& rotation, const glm::vec3& scale);

    void updateProgram(const glm::mat4 & view, const glm::mat4 & projection);

    /**
     * @brief loadObjs
     * @param objname
     * @return the good object with his different values
     */
    static std::shared_ptr<AsteroidObject> loadObjs(asteroid_t asteroidType, const std::string & objname,
                  std::shared_ptr<Program> program, const float health,
                  const glm::vec3& position, const glm::vec3& origin,
                  const glm::vec3& rotation, const glm::vec3& scale);

private:
    asteroid_t m_asteroidType;
    std::shared_ptr<RenderObject> m_object;
    std::shared_ptr<Program> m_program;//appel du program pour y mettre les objets
    std::shared_ptr<Sampler> m_colormap;
};

#endif // __ASTEROID_OBJECT_HPP__

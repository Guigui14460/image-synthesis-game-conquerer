#ifndef __PLAYER_OBJECT_HPP__
#define __PLAYER_OBJECT_HPP__
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "AbstractGameObject.hpp"
#include "glApi.hpp"
#include "RenderObjectConqueror.hpp"

/**
 * @brief The PlayerObject class
 *
 * the user need to move and rotate in the space with his object
 *
 *see in the objectLoader to call function
 *
 * redifine the move metod
 *
 * shoot system
 */
class PlayerObject: public AbstractGameObject {
public:
    enum player_t {PLAYER1, PLAYER2, COMPUTER, NONE};

    PlayerObject() = delete;
    PlayerObject(const PlayerObject &) = default;

    /**
     * @brief loadObjsPlayer
     * @param typePj
     * @return object of the player choice because of player's type
     */
    static std::shared_ptr<PlayerObject> loadObjsPlayer(player_t typePj, std::shared_ptr<Program> program, const float& health,
                                                        const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale);

    void update(float deltaTime) override;

    player_t getPlayerType();

    void setOrientation(const glm::vec3& orientation) {
        //this->rotate(orientation- this->m_orientation);
        this->m_orientation = orientation;
    }

    void inverseOrientation() {
        this->m_orientation *= -1;
        this->m_rotation *= -1;
    }

private:
    /**
     * @brief loadObjs
     * @param objname
     * @return the good object with his different values
     */
    static std::shared_ptr<PlayerObject> loadObjs(player_t typePj, const std::string & objname, std::shared_ptr<Program> program, const float& health,
                                                  const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale);

    PlayerObject(player_t typePj, std::shared_ptr<RenderObject> object, std::shared_ptr<Program> program, const float& health,
                 const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3 sizes = glm::vec3(SIZE_DEFAULT));

private:
    player_t m_typePj;
    glm::vec3 m_orientation;
};

#endif // __PLAYER_OBJECT_HPP__

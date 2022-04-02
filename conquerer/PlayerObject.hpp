#ifndef __PLAYER_OBJECT_HPP__
#define __PLAYER_OBJECT_HPP__
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "AbstractGameObject.hpp"
#include "glApi.hpp"
#include "RenderObjectConqueror.hpp"


enum player_t {PLAYER1, PLAYER2, COMPUTER};

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
    PlayerObject() = delete;
    PlayerObject(const PlayerObject &)= delete;

    /**
     * @brief loadObjsPlayer
     * @param typePj
     * @return object of the player choice because of player's type
     */
    static std::shared_ptr<PlayerObject> loadObjsPlayer(player_t typePj, glm::vec3 position, std::shared_ptr<Program> program);

    /**
     * @brief loadObjs
     * @param objname
     * @return the good object with his different values
     */
    static std::shared_ptr<PlayerObject> loadObjs(player_t typePj, const std::string & objname, glm::vec3 position, std::shared_ptr<Program> program);
    /**
     * @brief draw
     *
     * draw this object
     */
    void draw(const glm::mat4 & view, const glm::mat4 & projection);

    /**
     * @brief update
     *
     * update the program
     */
    void updateProgram(const glm::mat4 & view, const glm::mat4 & projection);

    void update(float deltaTime) override;

private:
    player_t m_typePj;
    std::shared_ptr<RenderObject> m_object;
    std::shared_ptr<Program> m_program;//appel du program pour y mettre les objets
    std::shared_ptr<Sampler> m_colormap;


    PlayerObject(player_t typePj, std::shared_ptr<RenderObject> object, glm::vec3 position,
                 std::shared_ptr<Program> program, std::shared_ptr<Sampler> m_colormap);
};

#endif // __PLAYER_OBJECT_HPP__

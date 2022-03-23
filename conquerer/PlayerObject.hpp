#ifndef __PLAYER_OBJECT_HPP__
#define __PLAYER_OBJECT_HPP__
#include "AbstractGameObject.hpp"
#include "glApi.hpp"
#include "Mesh.hpp"


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

class PlayerObject: public AbstractGameObject
{
private:
    player_t m_typePj;
    std::shared_ptr<Texture> m_texture;//fait avec le glApi
    std::shared_ptr<Mesh> m_mesh;//=VAO creer l'object en mémoire (prendre exemple sur le mesh)
    std::shared_ptr<Program> m_program;//appel du program pour y mettre les objets

    PlayerObject(player_t typePj, std::shared_ptr<Texture> texture,
                 std::shared_ptr<Mesh> mesh, glm::vec3 position,
                 std::shared_ptr<Program> program);

public:
    PlayerObject() = delete;
    PlayerObject(const PlayerObject &)= delete;

    /**
     * @brief loadObjsPlayer
     * @param typePj
     * @return object of the player choice because of player's type
     */
    static std::shared_ptr<PlayerObject> loadObjsPlayer(player_t typePj,  glm::vec3 position, std::shared_ptr<Program> program);

    /**
     * @brief loadObjs
     * @param objname
     * @return the good object with his different values
     */
    static std::shared_ptr<PlayerObject> loadObjs(player_t typePj, const std::string & objname, const std::string & texturename,glm::vec3 position, std::shared_ptr<Program> program);
    /**
     * @brief draw
     *
     * draw this object
     */
    void draw();

    /**
     * @brief update
     *
     * update the program
     */
    void update();

    ~PlayerObject(){}
};

#endif // __PLAYER_OBJECT_HPP__

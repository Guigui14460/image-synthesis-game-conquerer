#ifndef __PLAYER_OBJECT_HPP__
#define __PLAYER_OBJECT_HPP__
#include "AbstractGameObject.hpp"
#include "glApi.hpp"
#include "Model.hpp"


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
    PlayerObject(const PlayerObject &) = delete;
    ~PlayerObject(){}

    /**
     * @brief loadObjsPlayer
     * @param typePj
     * @return object of the player choice because of player's type
     */
    static std::shared_ptr<PlayerObject> loadObjsPlayer(player_t typePj, std::shared_ptr<Program> program, glm::vec3 position, glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));

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
    void update() override;

private:
    PlayerObject(player_t typePj, std::shared_ptr<Model> model, std::shared_ptr<Mesh> mesh, std::shared_ptr<VAO> vao,
                 std::shared_ptr<Program> program, std::shared_ptr<Sampler> colormap,
                 glm::vec3 position);

    /**
     * @brief loadObjs
     * @param objname
     * @return the good object with his different values
     */
    static std::shared_ptr<PlayerObject> loadObjs(player_t typePj, const std::string & objname, const std::string & texturename, std::shared_ptr<Program> program, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

private:
    player_t m_typePj;
    std::shared_ptr<VAO> m_vao;
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Model> m_model; //=VAO creer l'object en mémoire (prendre exemple sur le mesh)
    std::shared_ptr<Program> m_program; //appel du program pour y mettre les objets
    std::shared_ptr<Sampler> m_colormap;
};

#endif // __PLAYER_OBJECT_HPP__

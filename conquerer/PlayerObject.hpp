#ifndef __PLAYER_OBJECT_HPP__
#define __PLAYER_OBJECT_HPP__
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "AbstractGameObject.hpp"
#include "glApi.hpp"
#include "Mesh.hpp"
#include "RenderObjectConqueror.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

<<<<<<< HEAD


=======
>>>>>>> origin/game_logic
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
public:
<<<<<<< HEAD

    enum player_t {PLAYER1, PLAYER2, COMPUTER,  NONE};
=======
    enum player_t {PLAYER1, PLAYER2, COMPUTER, NONE};

>>>>>>> origin/game_logic
    PlayerObject() = delete;
    PlayerObject(const PlayerObject &) = default;

    ~PlayerObject(){}

    /**
     * @brief loadObjsPlayer
     * @param typePj
     * @return object of the player choice because of player's type
     */
    static std::shared_ptr<PlayerObject> loadObjsPlayer(player_t typePj,  glm::vec3 position, std::shared_ptr<Program> program, const float health);

    /**
     * @brief loadObjs
     * @param objname
     * @return the good object with his different values
     */
    static std::shared_ptr<PlayerObject> loadObjs(player_t typePj, const std::string & objname, const std::string & texturename,glm::vec3 position, std::shared_ptr<Program> program, const float health);
    /**
     * @brief draw
     *
     * draw this object
     */
<<<<<<< HEAD
    void draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES) override;
=======
    void draw(const glm::mat4& projViewMatrix, GLenum mode = GL_TRIANGLES) override;
>>>>>>> origin/game_logic

    /**
     * @brief update
     *
     * update the program
     */
<<<<<<< HEAD
    void update(const glm::mat4 & view, const glm::mat4 & projection);

    void update(){}

    void update(float deltaTime) override;
	
	 player_t getPlayerType();
	 
    ~PlayerObject(){}

private:
    player_t m_typePj;
//    RenderObjectConqueror m_objects;
    std::shared_ptr<RenderObject> m_object;
    std::shared_ptr<Program> m_program;//appel du program pour y mettre les objets
    //std::vector<std::shared_ptr<RenderObjectConqueror>> m_parts;
    std::shared_ptr<Sampler> m_colormap;


    PlayerObject(player_t typePj, std::shared_ptr<RenderObject> object, glm::vec3 position,
                 std::shared_ptr<Program> program,
                 //std::vector<std::shared_ptr<RenderObjectConqueror>> parts,
                 std::shared_ptr<Sampler> m_colormap);
=======
    void update(float deltaTime) override;

    player_t getPlayerType();
    void setOrientation(const glm::vec3& orientation) { this->m_orientation = orientation; }

private:
    player_t m_typePj;
    std::shared_ptr<Texture> m_texture;//fait avec le glApi
//    std::shared_ptr<Mesh> m_mesh;//=VAO creer l'object en mémoire (prendre exemple sur le mesh)
    std::shared_ptr<Program> m_program;//appel du program pour y mettre les objets
    glm::vec3 m_orientation;

    PlayerObject(player_t typePj, std::shared_ptr<Texture> texture,
                 std::shared_ptr<Mesh> mesh, glm::vec3 position,
                 std::shared_ptr<Program> program, const float health);

>>>>>>> origin/game_logic
};

#endif // __PLAYER_OBJECT_HPP__

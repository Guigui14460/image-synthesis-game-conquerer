#ifndef __PLAYER_OBJECT_HPP__
#define __PLAYER_OBJECT_HPP__
#include "AbstractGameObject.hpp"
#include "glApi.hpp"
#include "Mesh.hpp"
#include "RenderObjectConqueror.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>



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

    enum player_t {PLAYER1, PLAYER2, COMPUTER,  NONE};
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
    void draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES) override;

    /**
     * @brief update
     *
     * update the program
     */
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
};

#endif // __PLAYER_OBJECT_HPP__

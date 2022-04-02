#ifndef __MESH_HPP__
#define __MESH_HPP__
#include "glApi.hpp"

/**
 * @brief The Mesh class representing an instance VAO
 */
class Mesh
{
public:
    /**
     * @brief Mesh constructor
     * @param vao the object to store
     * @param position the current position of the object
     * @param origin the initial position of the object
     * @param rotate the initial rotation value of the object
     * @param scale the initial scale value of the object
     */
    Mesh(std::shared_ptr<VAO> vao, glm::vec3 position = glm::vec3(0.f), glm::vec3 origin = glm::vec3(0.f),
         glm::vec3 rotate = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
    ~Mesh() {} /// Destructor
    Mesh(const Mesh& o) = delete; /// Copy constructor
    Mesh(Mesh&& o) = delete; /// Moving constructor

    /// Gets the position the object
    inline glm::vec3 getPosition() const { return this->m_position; }
    /// Gets the origin the object
    inline glm::vec3 getOrigin() const { return this->m_origin; }
    /// Gets the rotation the object
    inline glm::vec3 getRotation() const { return this->m_rotation; }
    /// Gets the scale the object
    inline glm::vec3 getScale() const { return this->m_scale; }

    /**
     * @brief Sets a new position for the object.
     * @param position new position for the object
     */
    inline void setPosition(const glm::vec3& position) { this->m_position = position; }
    /**
     * @brief Sets a new origin for the object.
     * @param origin new origin for the object
     */
    inline void setOrigin(const glm::vec3& origin) { this->m_origin = origin; }
    /**
     * @brief Sets a new rotation for the object.
     * @param rotation new rotation for the object
     */
    inline void setRotation(const glm::vec3& rotation) { this->m_rotation = rotation; }
    /**
     * @brief Sets a new scale for the object.
     * @param scale new scale for the object
     */
    inline void setScale(const glm::vec3& scale) { this->m_scale = scale; }

<<<<<<< HEAD
<<<<<<< HEAD
    void updateProgram(Program& prog, const glm::mat4 & view, const glm::mat4 & projection);
=======
    void updateProgram(Program& prog, const glm::mat4& projViewMatrix);
>>>>>>> origin/game_logic
=======
    void updateProgram(Program& prog, const glm::mat4 & view, const glm::mat4 & projection);
>>>>>>> 76756a395e3f6928abbc77ab9f71bd0850d401ab

    /**
     * @brief Updates the object with an elapsed time between the last and current frames.
     * @param deltaTime elapsed time between the last and current frames
     */
    void update(float deltaTime);

    /**
     * @brief Moves the object to a new position (addition of the position).
     * @param position moving value to go
     */
    void move(const glm::vec3& position);

    /**
     * @brief Rotates the object to new angles (addition of the rotation).
     * @param rotation rotating value to go
     */
    void rotate(const glm::vec3& rotation);

    /**
     * @brief Zooms the object to new scale (addition of the scale).
     * @param scale scaling value to go
     */
    void zoom(const glm::vec3& scale);

    /**
     * @brief Renders a single frame of the object to the screen.
     * @param mode how to display the VAO (triangles, quads, polygons, etc)
     */
<<<<<<< HEAD
    void render(Program &prog, const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES);
=======
    void render(Program& prog, const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES);
>>>>>>> 76756a395e3f6928abbc77ab9f71bd0850d401ab

private:
    /// Updates the model matric of the object.
    void updateModelMatrix();

private:
    std::shared_ptr<VAO> m_vao; /// The object to display

    glm::vec3 m_position; /// 3D position to display the object
    glm::vec3 m_origin; /// 3D origin position of the object
    glm::vec3 m_rotation; /// 3D rotating value
    glm::vec3 m_scale; /// 3D scaling value

    glm::mat4 m_modelMatrix; /// The world matrix of the object
};

#endif // __MESH_HPP__

#ifndef __MESH_HPP__
#define __MESH_HPP__
#include <glm/mat4x4.hpp>

#include "glApi.hpp"
#include "AbstractRenderObject.hpp"

/**
 * @brief The Mesh class representing an instance VAO
 */
class Mesh: public AbstractRenderObject {
public:
    /**
     * @brief Mesh constructor
     * @param vao the object to store
     */
    Mesh(std::shared_ptr<VAO> vao);
    Mesh(const Mesh& o) = default; /// Copy constructor
    Mesh(Mesh&& o) = default; /// Moving constructor

    /**
     * @brief Renders a single frame of the object to the screen.
     * @param mode how to display the VAO (triangles, quads, polygons, etc)
     */
    void render(Program& prog, const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES) override;

private:
    void updateProgram(Program& prog, const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection);

private:
    std::shared_ptr<VAO> m_vao; /// The object to display
};

#endif // __MESH_HPP__

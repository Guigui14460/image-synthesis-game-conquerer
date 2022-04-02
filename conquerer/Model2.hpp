#ifndef __MODEL_HPP__
#define __MODEL_HPP__
#include <glm/mat4x4.hpp>
#include "glApi.hpp"
#include "Mesh.hpp"

/**
 * @brief The Model class represents a set of objects to display with the same texture.
 */
class Model {
public:
    /// Default constructor
    Model() = delete;

    /**
     * @brief Model constructor
     * @param meshes set of objects to render
     * @param diffuseTexture texture to map on objects
     */
    Model(std::vector<std::shared_ptr<Mesh>>& meshes, std::shared_ptr<Texture> diffuseTexture);

    /// Copy constructor
    Model(const Model& o) = delete;

    /**
     * @brief Updates the object with an elapsed time between the last and current frames.
     * @param deltaTime elapsed time between the last and current frames
     */
    void update(float deltaTime);

    /**
     * @brief Renders objects to the screen.
     * @param program to send uniforms
     * @param sampler for texture
     * @param projViewMatrix projection * view matrices
     * @param mode how to display the VAO (triangles, quads, polygons, etc)
     */
    void render(Program& program, Sampler& sampler, const glm::mat4& projViewMatrix, GLenum mode = GL_TRIANGLES);

    std::shared_ptr<Mesh> getMesh(unsigned int index);

private:
    std::vector<std::shared_ptr<Mesh>> m_meshes; /// Objects to display
    std::shared_ptr<Texture> m_diffuseTexture; /// Texture to display on each objects

};

#endif // __MODEL_HPP__
// TODO: faire méthode statique pour faciliter le chargement d'objets et de texture

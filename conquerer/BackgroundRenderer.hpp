#ifndef __BACKGROUND_RENDERER_HPP__
#define __BACKGROUND_RENDERER_HPP__
#include "glApi.hpp"
#include <vector>
#include "Mesh.hpp"
#include <glm/ext.hpp>

// forward declaration
struct GLFWwindow;

constexpr float PI = glm::pi<float>(); /// Pi constant
constexpr float MIN_ANGLE_BACKGROUND = 0.f; /// Min angle in radius
constexpr float MAX_ANGLE_BACKGROUND = 2.f * PI; /// Max angle in radius

/**
 * @brief The BackgroundRenderer class.
 *
 * Render the background space with random generated stars.
 */
class BackgroundRenderer
{
public:
    /**
     * @brief Constructor.
     * @param numberOfStars
     * @param universeRadius
     */
    BackgroundRenderer(uint numberOfStars, float universeRadius = 1.f);
    BackgroundRenderer(const BackgroundRenderer& o) = delete; /// Copy constructor
    BackgroundRenderer(BackgroundRenderer&& o) = delete; /// Moving constructor

    /**
     * @brief Updates the scene including meshes which is time related.
     * @param deltaTime
     */
    void update(float deltaTime);

    /**
     * @brief Renders a single frame.
     */
    void renderFrame(const glm::mat4& projViewMatrix);

private:
    /**
     * @brief Create the VAO for the renderer
     * @param numberOfStars
     * @param universeRadius
     */
    void createVAO(uint numberOfStars, float universeRadius);
    
    /**
     * @brief Generates random stars.
     * @param numberOfStars
     * @param universeRadius
     * @return a vector of 3D coordinates
     *
     * It generates the random angle, phi and theta to create in the polar coordinates.
     * It applies a mathematicla formula to transpose in the euclidan 3D space.
     */
    std::vector<glm::vec3> generateRandomStars(uint numberOfStars, float universeRadius);

    /**
     * @brief Generates random stars sizes.
     * @param numberOfStars
     * @param min min size of the random engine
     * @param max max size of the random engine
     * @return a vector of float representing a scaling value. There is the same number of sizes that number of stars
     */
    std::vector<float> generateRandomSizes(uint numberOfStars, float min, float max);


private:
    std::vector<std::shared_ptr<Mesh>> m_meshes; /// Meshes (VAO + associated model matrix)
    std::shared_ptr<VAO> m_vao; /// The default VAO (3D sphere)
    Program m_program; /// GLSL Program used for the render of 3D space
};

#endif // __BACKGROUND_RENDERER_HPP__

#ifndef __BACKGROUND_RENDERER_HPP__
#define __BACKGROUND_RENDERER_HPP__
#include <vector>
#include <glm/ext.hpp>
#include "glApi.hpp"
#include "PlanetObject.hpp"

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
class BackgroundRenderer {
public:
    /**
     * @brief Constructor.
     * @param numberOfStars
     * @param universeRadius
     */
    BackgroundRenderer(uint numberOfStars, float universeRadius = 1.f, const glm::vec3& origin = glm::vec3(0.f));
    BackgroundRenderer(const BackgroundRenderer& o) = delete; /// Copy constructor
    BackgroundRenderer(BackgroundRenderer&& o) = delete; /// Moving constructor

    /**
     * @brief Updates the scene including meshes which is time related.
     */
    void update(float deltaTime);

    /**
     * @brief Renders a single frame.
     */
    void renderFrame(const glm::mat4 & view, const glm::mat4 & projection);

private:
    /**
     * @brief Create the VAO for the renderer
     * @param numberOfStars
     * @param universeRadius
     */
    void createVAO(uint numberOfStars, float universeRadius, const glm::vec3& origin);
    
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
    std::vector<std::shared_ptr<PlanetObject>> m_stars;
    std::shared_ptr<VAO> m_vao; /// The default VAO (3D sphere)
};

#endif // __BACKGROUND_RENDERER_HPP__

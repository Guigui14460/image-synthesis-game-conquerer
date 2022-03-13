#ifndef __BACKGROUND_RENDERER_HPP__
#define __BACKGROUND_RENDERER_HPP__
#include "glApi.hpp"
#include <cmath>
#include <vector>
#include <glm/ext.hpp>
#include "Mesh.hpp"

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
     */
    BackgroundRenderer(uint numberOfStars);
    BackgroundRenderer(const BackgroundRenderer& o) = delete; /// Copy constructor
    BackgroundRenderer(const BackgroundRenderer&& o) = delete; /// Moving constructor

    /**
     * @brief Iniitializes the OpenGL state for this renderer.
     */
    void initGLState() const;

    /**
     * @brief Create the VAO for the renderer
     * @param numberOfStars
     */
    void createVAO(uint numberOfStars);

    /**
     * @brief Resizes the render screen to fit with the GLFW window screen size.
     * @param window the GLFW window object
     * @param frameBufferWidth the new width of the frame buffer to display
     * @param frameBufferHeight the new height of the frame buffer to display
     */
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);

    /**
     * @brief Updates the scene including meshes which is time related.
     */
    void update();

    /**
     * @brief Method which used to interact with the keyboard user.
     */
    void continuousKey();

    /**
     * @brief Renders a single frame.
     */
    void renderFrame();

private:
    /**
     * @brief Generates random stars.
     * @param numberOfStars
     * @return a vector of 3D coordinates
     *
     * It generates the random angle, phi and theta to create in the polar coordinates.
     * It applies a mathematicla formula to transpose in the euclidan 3D space.
     */
    std::vector<glm::vec3> generateRandomStars(uint numberOfStars);

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
    glm::mat4 m_proj; /// Projection matrix
    glm::mat4 m_view; /// View matrix

    float m_eyePhi; /// Theta angle for the camera
    float m_eyeTheta; /// Phi angle for the camera

    float m_currentTime; /// Current OpenGL time
    float m_deltaTime; /// Elapsed time between last frame and current showing frame for the animation speed
};

#endif // __BACKGROUND_RENDERER_HPP__

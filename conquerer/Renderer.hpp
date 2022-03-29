#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__
#include <glm/mat4x4.hpp>
#include "glApi.hpp"
#include "Camera.hpp"
#include "GameLogic.hpp"
#include "BackgroundRenderer.hpp"
#include "GameOverlay.hpp"

struct camera_t {
    Camera camera;
    glm::mat4 projection;
    glm::mat4 view;
};

class Renderer {
public:
    enum renderer_part_t {LEFT_PART, RIGHT_PART};

    /// Default constructor
    Renderer();

    /// Destructor
    ~Renderer() {}

    /// OpenGL state initialization
    void initGLState() const;

    /**
     * @brief Resizes the render screen to fit with the GLFW window screen size.
     * @param window the GLFW window object
     * @param frameBufferWidth the new width of the frame buffer to display
     * @param frameBufferHeight the new height of the frame buffer to display
     */
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);

    /// Renders a single frame to the screen.
    void renderFrame();

    /// Updates the time related objects.
    void update();

private:
    /// Render part of the screen
    void renderPart(renderer_part_t part);

private:
    bool m_leftPartIsPlayer1;
    int m_frameBufferWidth; /// The width of the current viewport
    int m_frameBufferHeight; /// The height of the current viewport
    camera_t m_cameraPlayer1, m_cameraPlayer2;
    float m_currentTime, m_deltaTime;
//    GameLogic m_logic;
    BackgroundRenderer m_background;
    GameOverlay m_overlay;
};

#endif // __RENDERER_HPP__

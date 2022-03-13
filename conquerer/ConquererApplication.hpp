#ifndef __CONQUERER_APPLICATION_HPP__
#define __CONQUERER_APPLICATION_HPP__
#include "FullScreenApplication.hpp"
#include "glApi.hpp"
#include "GameStage.hpp"

/**
 * @brief The concrete application of the Conquerer game
 */
class ConquererApplication: public WindowedApplication {
public:
    /// Default constructor
    ConquererApplication();

    /// Sets the callbacks (key, resize)
    void setCallbacks() override;

    /**
     * @brief Main application loop
     *
     * Continues until 'Esc' is pressed.
     */
    void mainLoop();

private:
    /// Renders a single frame
    void renderFrame() override;

    /// Updates the time related members
    void update() override;

    /**
     * @brief Resizes the render screen to fit with the GLFW window screen size.
     * @param window the GLFW window object
     * @param frameBufferWidth the new width of the frame buffer to display
     * @param frameBufferHeight the new height of the frame buffer to display
     */
    static void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);

    /// Key callback
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// Next stage to display
    void nextStage();

private:
    std::unique_ptr<GameStage> m_stage; /// Menu of the game
};

#endif // __CONQUERER_APPLICATION_HPP__

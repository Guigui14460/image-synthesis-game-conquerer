#ifndef __CONQUERER_APPLICATION_HPP__
#define __CONQUERER_APPLICATION_HPP__
#include "FullScreenApplication.hpp"
#include "GameStage.hpp"
#include "StartStage.hpp"

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

    /// Window resize callback
    static void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);

    /// Key callback
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// Next stage to display
    void nextStage();

private:
    std::unique_ptr<GameStage> m_stage; /// menu of the game
};

#endif // __CONQUERER_APPLICATION_HPP__

#ifndef __GAME_STAGE_HPP__
#define __GAME_STAGE_HPP__
#include "glApi.hpp"
#include <GLFW/glfw3.h>

/**
 * @brief The GameStage class is an abstract class to be derived by the concrete stages of the Conquerer application.
 */
class GameStage {
public:
    GameStage(); /// Default constructor
    GameStage(const GameStage& o) = delete; /// Copy constructor
    GameStage(GameStage &&o) = delete; /// Moving constructor

    /// Destructor
    virtual ~GameStage() {}

    /// Renders a single frame to the screen
    virtual void renderFrame() = 0;

    /// Updates the time related objects.
    virtual void update() = 0;

    /// Next stage to display
    virtual std::unique_ptr<GameStage> nextStage() const = 0;

    /// Key callback
    virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

    /**
     * @brief Resizes the render screen to fit with the GLFW window screen size.
     * @param window the GLFW window object
     * @param frameBufferWidth the new width of the frame buffer to display
     * @param frameBufferHeight the new height of the frame buffer to display
     */
    virtual void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) = 0;
};

#endif // __GAME_STAGE_HPP__

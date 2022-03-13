#ifndef __START_STAGE_HPP__
#define __START_STAGE_HPP__
#include "GameStage.hpp"
#include "TextPrinter.hpp"
#include "BackgroundRenderer.hpp"

/**
 * @brief The StartStage class represents the first stage of the Conquerer application showing the name of the application and allows to play the game.
 */
class StartStage final: public GameStage {
public:
    /// Default constructor
    StartStage();

    /// Destructor
    ~StartStage();

    /// Renders a single frame to the screen.
    void renderFrame() override;

    /// Updates the time related objects.
    void update() override;

    /// Key callback
    void keyCallback(GLFWwindow*, int, int, int, int) override {}

    /**
     * @brief Resizes the render screen to fit with the GLFW window screen size.
     * @param window the GLFW window object
     * @param frameBufferWidth the new width of the frame buffer to display
     * @param frameBufferHeight the new height of the frame buffer to display
     */
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) override;

    /// Next stage to display
    std::unique_ptr<GameStage> nextStage() const override;

private:
    std::unique_ptr<TextPrinter> m_text; /// To display some text
    BackgroundRenderer m_renderer;
};

#endif // __START_STAGE_HPP__

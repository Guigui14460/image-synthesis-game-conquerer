#ifndef __END_STAGE_HPP__
#define __END_STAGE_HPP__
#include "GameStage.hpp"
#include "TextPrinter.hpp"
#include "Renderer.hpp"

/**
 * @brief The EndStage class represents the final stage of the Conquerer application showing the winner.
 */
class EndStage final: public GameStage {
public:
    /// Default constructor
    EndStage(const std::shared_ptr<Renderer>& renderer);

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

    stage_t getStageType() override { return END; }

    /// Next stage to display
    std::unique_ptr<GameStage> nextStage() const override;

private:
    std::unique_ptr<TextPrinter> m_text; /// To display some text
    std::shared_ptr<Renderer> m_renderer; /// To display all objects
};

#endif // __END_STAGE_HPP__

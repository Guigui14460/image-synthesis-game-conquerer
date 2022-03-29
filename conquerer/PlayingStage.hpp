#ifndef __PLAYING_STAGE_HPP__
#define __PLAYING_STAGE_HPP__
#include "GameStage.hpp"
#include "BackgroundRenderer.hpp"
#include "PlayerObject.hpp"

class PlayingStage final: public GameStage
{
public:
    /// Default constructor
    PlayingStage();

    /// Destructor
    ~PlayingStage();

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
    std::shared_ptr<BackgroundRenderer> m_background_renderer; /// The background space renderer
    int m_frameBufferWidth; /// The width of the current viewport
    int m_frameBufferHeight; /// The height of the current viewport
    std::shared_ptr<PlayerObject> m_player_object;
};

#endif // __PLAYING_STAGE_HPP__

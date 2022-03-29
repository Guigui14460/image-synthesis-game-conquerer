#ifndef __PLAYING_STAGE_HPP__
#define __PLAYING_STAGE_HPP__
#include "glApi.hpp"
#include "GameStage.hpp"
#include "Renderer.hpp"
#include "BackgroundRenderer.hpp"

class PlayingStage final: public GameStage {
public:
    /// Default constructor
    PlayingStage(const std::shared_ptr<Renderer>& renderer);

    /// Destructor
    ~PlayingStage();

    /// Renders a single frame to the screen.
    void renderFrame() override;

    /// Updates the time related objects.
    void update() override;

    /// Key callback
    void keyCallback(GLFWwindow*, int, int, int, int) override;

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
    std::shared_ptr<Renderer> m_renderer;
};

#endif // __PLAYING_STAGE_HPP__

// TODO:
// - faire méthodes pour update le renderer
// - créer le système pour caméra
// - relier les camera et les objet jouables

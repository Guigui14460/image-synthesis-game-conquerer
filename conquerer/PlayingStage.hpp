#ifndef __PLAYING_STAGE_HPP__
#define __PLAYING_STAGE_HPP__
#include "GameStage.hpp"
#include "BackgroundRenderer.hpp"

class PlayingStage final: public GameStage
{
public:
    PlayingStage();
    ~PlayingStage();

    void renderFrame() override;
    void update() override;
    void keyCallback(GLFWwindow*, int, int, int, int) override {}
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) override;
    std::unique_ptr<GameStage> nextStage() const override;

private:
    BackgroundRenderer m_background_renderer;
};

#endif // __PLAYING_STAGE_HPP__

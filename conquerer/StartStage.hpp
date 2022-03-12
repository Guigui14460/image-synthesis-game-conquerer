#ifndef __START_STAGE_HPP__
#define __START_STAGE_HPP__
#include "GameStage.hpp"
#include "TextPrinter.hpp"

class StartStage final: public GameStage {
public:
    StartStage();
    ~StartStage();

    void renderFrame() override;
    void update() override;
    void keyCallback(GLFWwindow*, int, int, int, int) override {}
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) override;
    std::unique_ptr<GameStage> nextStage() const override;

private:
    std::unique_ptr<TextPrinter> m_text;
    //Renderer m_renderer;
};

#endif // __START_STAGE_HPP__

#ifndef __END_STAGE_HPP__
#define __END_STAGE_HPP__
#include "GameStage.hpp"
#include <GLFW/glfw3.h>
#include "TextPrinter.hpp"

class EndStage final: public GameStage {
public:
    EndStage();
    ~EndStage();

    void renderFrame() override;
    void update() override;
    void keyCallback(GLFWwindow*, int, int, int, int) override {}
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) override;
    std::unique_ptr<GameStage> nextStage() const override;

private:
    std::unique_ptr<TextPrinter> m_text;
    //Renderer m_renderer;
};

#endif // __END_STAGE_HPP__

#ifndef __CONQUERER_APPLICATION_HPP__
#define __CONQUERER_APPLICATION_HPP__
#include "Application.hpp"
#include "GameStage.hpp"
#include "StartStage.hpp"

class ConquererApplication: public Application {
public:
    ConquererApplication();

    void setCallbacks() override;

private:
    void renderFrame() override;
    void update() override;
    static void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void nextStage();

private:
    std::unique_ptr<GameStage> m_stage;
};

#endif // __CONQUERER_APPLICATION_HPP__

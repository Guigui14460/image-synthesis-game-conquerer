#ifndef __GAME_STAGE_HPP__
#define __GAME_STAGE_HPP__
#include "glApi.hpp"
#include <GLFW/glfw3.h>

class GameStage {
public:
    virtual void renderFrame() = 0;
    virtual void update() = 0;
    virtual std::unique_ptr<GameStage> nextStage() const = 0;
    virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
    virtual void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) = 0;
    virtual ~GameStage() {}
};

#endif // __GAME_STAGE_HPP__

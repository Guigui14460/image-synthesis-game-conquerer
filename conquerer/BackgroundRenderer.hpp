#ifndef __BACKGROUND_RENDERER_HPP__
#define __BACKGROUND_RENDERER_HPP__
#include "glApi.hpp"

struct GLFWwindow;

class BackgroundRenderer
{
public:
    BackgroundRenderer();

    void initGLState() const;
    void createVAO();
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);
    void update();
    void renderFrame();

private:
    std::shared_ptr<VAO> m_vao;
    Program m_program;
    glm::mat4 m_proj;
    glm::mat4 m_view;
    float m_currentTime;
    float m_deltaTime;
};

#endif // __BACKGROUND_RENDERER_HPP__

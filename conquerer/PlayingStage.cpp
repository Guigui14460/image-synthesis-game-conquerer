#include "PlayingStage.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

PlayingStage::PlayingStage(): m_background_renderer(new BackgroundRenderer(1000)) {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetFramebufferSize(window, &this->m_frameBufferWidth, &this->m_frameBufferHeight);
}

PlayingStage::~PlayingStage() {}

void PlayingStage::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    this->m_background_renderer->renderFrame();

    // for the split screen support (to fix with the matrices send as uniform)
    this->m_background_renderer->resize(nullptr, this->m_frameBufferWidth/2 - 1, this->m_frameBufferHeight);
    glViewport(0, 0, this->m_frameBufferWidth/2, this->m_frameBufferHeight);
    this->m_background_renderer->renderFrame();

    glViewport(this->m_frameBufferWidth/2 + 1, 0, this->m_frameBufferWidth/2, this->m_frameBufferHeight);
    this->m_background_renderer->renderFrame();

    this->m_background_renderer->resize(nullptr, this->m_frameBufferWidth, this->m_frameBufferHeight);
    glViewport(0, 0, this->m_frameBufferWidth, this->m_frameBufferHeight);
}

void PlayingStage::update() {
    this->m_background_renderer->update();
}

void PlayingStage::resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) {
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    this->m_frameBufferWidth = frameBufferWidth;
    this->m_frameBufferHeight = frameBufferHeight;

    this->m_background_renderer->resize(window, frameBufferWidth, frameBufferHeight);
}

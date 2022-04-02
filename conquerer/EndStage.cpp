#include "EndStage.hpp"
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

EndStage::EndStage(const std::shared_ptr<Renderer>& renderer)
    : m_renderer(renderer) {
    int frameBufferWidth, frameBufferHeight;
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

    this->m_text = std::unique_ptr<TextPrinter>(new TextPrinter(frameBufferWidth, frameBufferHeight));
    const glm::vec3 red(1, 0, 0);
    this->m_text->printText("gameover", "GAME OVER", 1, 7, 9, red);
}

void EndStage::renderFrame() {
    this->m_renderer->renderFrame();
    this->m_text->draw();
}

void EndStage::update() {
    this->m_renderer->update();
}

void EndStage::resize(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
    this->m_renderer->resize(window, frameBufferWidth, frameBufferHeight);
    this->m_text->resize(frameBufferWidth, frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

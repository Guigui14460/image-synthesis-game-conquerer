#include "EndStage.hpp"
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

EndStage::EndStage(const std::shared_ptr<BackgroundRenderer> renderer)
    : m_renderer(renderer) {
    int width, height;
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetFramebufferSize(window, &width, &height);

    this->m_text = std::unique_ptr<TextPrinter>(new TextPrinter(width, height));
    const glm::vec3 red(1, 0, 0);
    this->m_text->printText("GAME OVER", 1, 7, 9, red);
}

EndStage::~EndStage() {}

void EndStage::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render frame of renderer
    this->m_renderer->renderFrame();
    this->m_text->draw();
}

void EndStage::update() {
    // update the renderer
    this->m_renderer->update(false);
}

void EndStage::resize(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
    // resize the renderer
    this->m_renderer->resize(window, frameBufferWidth, frameBufferHeight);
    this->m_text->setWOverH(frameBufferWidth / float(frameBufferHeight));
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

#include "StartStage.hpp"
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

StartStage::StartStage() : m_renderer(new Renderer(true)) {
    int width, height;
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetFramebufferSize(window, &width, &height);

    this->m_text = std::unique_ptr<TextPrinter>(new TextPrinter(width, height));

    this->m_text->printText("CONQUERER", 0.5, 2, 10, {1.f, 0.f, 0.f});

    const glm::vec3 color(1.f, 1.f, 1.f);
    this->m_text->printText("Press Enter", 7, 20, 4, color);
    this->m_text->printText(" to  START ", 7, 21, 4, color);
}

StartStage::~StartStage() {}

void StartStage::renderFrame() {
    // render frame of renderer
    this->m_renderer->renderFrame();
    this->m_text->draw();
}

void StartStage::update() {
    // update the renderer
    this->m_renderer->update();
}

void StartStage::resize(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
    // resize the renderer
    this->m_renderer->resize(window, frameBufferWidth, frameBufferHeight);
    this->m_text->resize(frameBufferWidth, frameBufferHeight);
    this->m_text->setWOverH(frameBufferWidth / float(frameBufferHeight));
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

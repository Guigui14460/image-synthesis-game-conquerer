#include "PlayingStage.hpp"
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

PlayingStage::PlayingStage(): m_background_renderer(1000) {}

PlayingStage::~PlayingStage() {}

void PlayingStage::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_background_renderer.renderFrame();
}

void PlayingStage::update() {
    this->m_background_renderer.update();
}

void PlayingStage::resize(GLFWwindow*, int frameBufferWidth, int frameBufferHeight) {
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

#include "PlayingStage.hpp"
#include "PlayerObject.hpp"
#include "glApi.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

PlayingStage::PlayingStage(): m_background_renderer(new BackgroundRenderer(1000)) {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetFramebufferSize(window, &this->m_frameBufferWidth, &this->m_frameBufferHeight);
    m_player_object = PlayerObject::loadObjsPlayer(PLAYER1, std::make_shared<Program>("conquerer/3d.v.glsl", "conquerer/3d.f.glsl"), {0.f, 0.f, 0.f});
    glClearColor(1., 1., 1., 1.);
}

PlayingStage::~PlayingStage() {}

void PlayingStage::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    this->m_background_renderer->renderFrame();
    m_player_object->draw();

    // for the split screen support (to fix with the matrices send as uniform)
//    this->m_background_renderer->resize(nullptr, this->m_frameBufferWidth/2 - 1, this->m_frameBufferHeight);
//    glViewport(0, 0, this->m_frameBufferWidth/2, this->m_frameBufferHeight);
//    this->m_background_renderer->renderFrame();

//    glViewport(this->m_frameBufferWidth/2 + 1, 0, this->m_frameBufferWidth/2, this->m_frameBufferHeight);
//    this->m_background_renderer->renderFrame();

//    this->m_background_renderer->resize(nullptr, this->m_frameBufferWidth, this->m_frameBufferHeight);
//    glViewport(0, 0, this->m_frameBufferWidth, this->m_frameBufferHeight);
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

#include "Renderer.hpp"
#include <GLFW/glfw3.h>

Renderer::Renderer() : m_background(new BackgroundRenderer(250)), m_currentTime(0), m_deltaTime(0) {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetFramebufferSize(window, &this->m_frameBufferWidth, &this->m_frameBufferHeight);
}

void Renderer::initGLState() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::resize(GLFWwindow*, int frameBufferWidth, int frameBufferHeight) {
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    this->m_frameBufferWidth = frameBufferWidth;
    this->m_frameBufferHeight = frameBufferHeight;

    this->m_cameraPlayer1.camera.calculateProjectionMatrix(90., frameBufferWidth, frameBufferHeight, .1, 100.);
    this->m_cameraPlayer2.camera.calculateProjectionMatrix(90., frameBufferWidth, frameBufferHeight, .1, 100.);
}



void Renderer::update() {
    float prevTime = this->m_currentTime;
    this->m_currentTime = glfwGetTime();
    this->m_deltaTime = this->m_currentTime - prevTime;

    if(activateContinuousKeys){
        this->continuousKey();
    }

    this->m_cameraPlayer1.view = this->m_cameraPlayer1.camera.calculateViewMatrix();
    this->m_cameraPlayer2.view = this->m_cameraPlayer2.camera.calculateViewMatrix();


    this->m_background.update();
    this->m_overlay.update(0);
}

void Renderer::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_background.resize(nullptr, this->m_frameBufferWidth/2 - 1, this->m_frameBufferHeight);

    this->renderPart(LEFT_PART);
    this->renderPart(RIGHT_PART);

    glViewport(0, 0, this->m_frameBufferWidth, this->m_frameBufferHeight);
    this->m_background.resize(nullptr, this->m_frameBufferWidth, this->m_frameBufferHeight);

    this->m_overlay.render();
}

void Renderer::renderPart(renderer_part_t part) {
    camera_t cameraToUse = this->m_cameraPlayer1;
    int minX = 0, maxX = this->m_frameBufferWidth/2;
    if(part == RIGHT_PART){
        minX = maxX + 1;
        maxX = this->m_frameBufferWidth;
        cameraToUse = this->m_cameraPlayer2;
    }

    glViewport(minX, 0, maxX, this->m_frameBufferHeight);

    this->m_background.renderFrame(cameraToUse.view, cameraToUse.projection);
    // TODO: render other game objects
}

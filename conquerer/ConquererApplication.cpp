#include "ConquererApplication.hpp"
#include <GLFW/glfw3.h>

ConquererApplication::ConquererApplication()
    : WindowedApplication(1400, 850, "Conquerer Game"), m_stage(new StartStage()) {
}

void ConquererApplication::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(this->m_stage){
        m_stage->renderFrame();
    }
}

void ConquererApplication::mainLoop()
{
    GLFWwindow* window = glfwGetCurrentContext();
    while (!glfwWindowShouldClose(window)) {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        break;
      }

      update();
      renderFrame();

      // swap back and front buffers
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
}

void ConquererApplication::update() {
    this->m_stage->update();
}

void ConquererApplication::nextStage() {
    this->m_stage = this->m_stage->nextStage();
}

void ConquererApplication::resize(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
    ConquererApplication& app = *static_cast<ConquererApplication*>(glfwGetWindowUserPointer(window));
    app.m_stage->resize(window, frameBufferWidth, frameBufferHeight);
}

void ConquererApplication::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    ConquererApplication& app = *static_cast<ConquererApplication*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS){
        switch(key){
          case GLFW_KEY_ENTER:
            app.nextStage();
              return;
          default:
            break;
        }
    }
    app.m_stage->keyCallback(window, key, scancode, action, mods);
}

void ConquererApplication::setCallbacks() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetFramebufferSizeCallback(window, ConquererApplication::resize);
    glfwSetKeyCallback(window, ConquererApplication::keyCallback);
}

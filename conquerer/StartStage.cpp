#include "StartStage.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

StartStage::StartStage()
{
  glClearColor(1.f, 1.f, 1.f, 1.f);
  int width, height;
  GLFWwindow* window = glfwGetCurrentContext();
  glfwGetFramebufferSize(window, &width, &height);

  this->m_text = std::unique_ptr<TextPrinter>(new TextPrinter(width, height));
  const glm::vec3 color(0.f, 0.f, 0.f);
  this->m_text->printText("Press Enter", 4, 12, 5, color);
  this->m_text->printText(" to  START ", 4, 13, 5, color);
}

StartStage::~StartStage() {}

void StartStage::renderFrame() {
  // render frame of renderer
  this->m_text->draw();
}

void StartStage::update() {
    // update the renderer
}

void StartStage::resize(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
  // resize the renderer
  this->m_text->setWOverH(frameBufferWidth / float(frameBufferHeight));
  glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

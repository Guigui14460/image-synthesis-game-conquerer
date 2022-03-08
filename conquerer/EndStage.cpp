#include "EndStage.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "StartStage.hpp"

EndStage::EndStage()
{
  glClearColor(1, 0.7, 0.4, 1);
  int width, height;
  GLFWwindow* window = glfwGetCurrentContext();
  glfwGetFramebufferSize(window, &width, &height);

  this->m_text = std::unique_ptr<TextPrinter>(new TextPrinter(width, height));
  const glm::vec3 red(1, 0, 0);
  this->m_text->printText("GAME OVER", 4, 12, 5, red);
}

EndStage::~EndStage() {}

void EndStage::renderFrame() {
  glClear(GL_COLOR_BUFFER_BIT);
  // render frame of renderer
  this->m_text->draw();
}

void EndStage::update() {
    // update the renderer
}

void EndStage::resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) {
  // resize the renderer
  this->m_text->setWOverH(frameBufferWidth / float(frameBufferHeight));
  glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

std::unique_ptr<GameStage> StartStage::nextStage() const {
  return std::unique_ptr<GameStage>(new EndStage());
}

std::unique_ptr<GameStage> EndStage::nextStage() const {
  return std::unique_ptr<GameStage>(new StartStage());
}

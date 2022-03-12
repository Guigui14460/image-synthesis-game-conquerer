#include "BackgroundRenderer.hpp"
#include <GLFW/glfw3.h>
//#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

BackgroundRenderer::BackgroundRenderer()
    : m_program("conquerer/3d.v.glsl", "conquerer/3d.f.glsl"), m_view(1), m_currentTime(0), m_deltaTime(0)
{
    GLFWwindow* window = glfwGetCurrentContext();
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    this->resize(window, windowWidth, windowHeight);
    this->initGLState();
    this->createVAO();
}

void BackgroundRenderer::initGLState() const {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void BackgroundRenderer::createVAO() {

}

void BackgroundRenderer::renderFrame()
{
  this->m_program.bind();

  glm::mat4 view(1);
  const float pi = glm::pi<float>();
  view = glm::rotate(glm::mat4(1), pi / 7, {0, 1, 0});
  view = glm::rotate(glm::mat4(1), -pi / 4, {1, 0, 0}) * view * m_view;

//  this->m_vao->updateProgram(this->m_program, m_proj, view);
//  this->m_vao->draw();

  this->m_program.unbind();
}

void BackgroundRenderer::update() {
    float prevTime = this->m_currentTime;
    this->m_currentTime = glfwGetTime();
    this->m_deltaTime = this->m_currentTime - prevTime;

    this->m_program.bind();
//    this->m_program.setUniform("time", this->m_currentTime);
    this->m_program.unbind();

//    for (auto & vao : m_vaos) {
//      vao->update(this->m_deltaTime);
//    }
}


void BackgroundRenderer::resize(GLFWwindow*, int frameBufferWidth, int frameBufferHeight)
{
  float aspect = frameBufferHeight / float(frameBufferWidth);
  if (aspect > 1) {
    m_proj = glm::ortho(-1.f, 1.f, -aspect, aspect);
  } else {
    m_proj = glm::ortho(-1 / aspect, 1 / aspect, -1.f, 1.f);
  }
}

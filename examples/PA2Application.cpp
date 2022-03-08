#define GLM_FORCE_RADIANS
#include "PA2Application.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "utils.hpp"

PA2Application::PA2Application(int windowWidth, int windowHeight)
    : Application(windowWidth, windowHeight, "Application for PA2"), m_vao(2), m_program("shaders/simple3d.v.glsl", "shaders/simple3d.f.glsl"), m_currentTime(0)
{
  makeA3dCube();
}

void PA2Application::makeA3dCube()
{
  std::vector<glm::vec3> positions = {
      // back
      {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5},
      {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5},

      // front
      {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
      {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5},

      // left
      {-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5},
      {-0.5, 0.5, 0.5}, {-0.5, 0.5, -0.5},

      // right
      {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5},
      {0.5, 0.5, 0.5}, {0.5, 0.5, -0.5},

      // up
      {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5},
      {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5},

      // down
      {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
      {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5},
  };
  std::vector<glm::vec3> colors = {
      {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {1, 1, 0},
      {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
      {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0},
      {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1},
      {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1},
      {0, 1, 1}, {0, 1, 1}, {0, 1, 1}, {0, 1, 1},
  };
  std::vector<uint> ibo = {
      0, 1, 2, 0, 2, 3,
      4, 5, 6, 4, 6, 7,
      8, 9, 10, 8, 10, 11,
      12, 13, 14, 12, 14, 15,
      16, 17, 18, 16, 18, 19,
      20, 21, 22, 20, 22, 23,
  };
  m_vao.setVBO(0, positions);
  m_vao.setVBO(1, colors);
  m_vao.setIBO(ibo);
}

void PA2Application::renderFrame()
{
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  m_program.bind();

  glm::vec3 eye(0, 0, -5), center(0, 1, 0), up(0, 0, 1);

  glm::mat4 m(1);
  glm::mat4 v = glm::lookAt(eye, center, up);
  glm::mat4 p = glm::perspective(static_cast<float>(M_PI/4), static_cast<float>(1024./860.), 0.1f, 100.f);

  m = glm::translate(m, {0.5, 0.5, 0.5});
  m = glm::rotate(m, glm::radians(10.f)*m_currentTime, {1, 1, 0});
  m = glm::scale(m, glm::vec3(0.5f));
  m_program.setUniform("M", m);
  m_program.setUniform("V", v);
  m_program.setUniform("P", p);
  m_vao.draw(); // rendering first instance

  m = glm::mat4(1);
  m = glm::translate(m, {-0.5, -0.5, -0.5});
  m = glm::rotate(m, glm::radians(10.f)*m_currentTime, {1, 1, 0});
  m_program.setUniform("M", m);
  m_program.setUniform("V", v);
  m_program.setUniform("P", p);
  m_vao.draw(); // rendering second instance
  m_program.unbind();
}

void PA2Application::update()
{
  m_currentTime = glfwGetTime();
  m_program.bind();
  m_program.setUniform("time", m_currentTime);
  m_program.unbind();
}

void PA2Application::resize(GLFWwindow *, int framebufferWidth, int framebufferHeight)
{
  glViewport(0, 0, framebufferWidth, framebufferHeight);
}

void PA2Application::setCallbacks()
{
  GLFWwindow * window = glfwGetCurrentContext();
  glfwSetFramebufferSizeCallback(window, PA2Application::resize);
}

void PA2Application::usage(std::string & shortDescritpion, std::string & synopsis, std::string & description)
{
  shortDescritpion = "Application for programming assignment 2";
  synopsis = "pa2";
  description = "  An application on GLSL uniform variables and true 3D meshes.\n";
}

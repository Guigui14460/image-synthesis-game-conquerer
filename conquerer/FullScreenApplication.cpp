#include "FullScreenApplication.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utils.hpp"

FullScreenApplication::FullScreenApplication(const char *title){
    this->initOGLContext(title);
}

FullScreenApplication::~FullScreenApplication() {
    this->shutDown(EXIT_SUCCESS);
}

void FullScreenApplication::mainLoop() {
  GLFWwindow* window = glfwGetCurrentContext();

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        break;
    }

    //if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
    update();
    //}

    renderFrame();

    // swap back and front buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

glm::vec2 FullScreenApplication::getWindowSize() {
    GLFWwindow* window = glfwGetCurrentContext();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    return glm::vec2(width, height);
}

void FullScreenApplication::initGLFW() {
    if(!glfwInit()){
        std::cerr << "ERROR::FullScreenApllication::initGLFW::GLFW_INIT_FAILED" << std::endl;
        this->shutDown(EXIT_FAILURE);
    }
}

void FullScreenApplication::initGLEW() {
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    checkGLerror();
    if (GlewInitResult != GLEW_OK) {
        std::cerr << "ERROR::FullScreenApllication::initGLEW::GLEW_INIT_FAILED : " << glewGetErrorString(GlewInitResult) << std::endl;
        this->shutDown(EXIT_FAILURE);
    }
}

void FullScreenApplication::initWindow(const char *title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#if defined(MACOS) || defined(__APPLE__)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //glfwWindowHint(GLFW_DECORATED, NULL);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    const int width = mode->width;
    const int height = mode->height;

    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, NULL);
    if (!window) {
        std::cerr << "ERROR::FullScreenApplication::initWindow : Could not open a window" << std::endl;
        this->shutDown(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
}

void FullScreenApplication::initOGLContext(const char *title) {
    this->initGLFW();
    this->initWindow(title);
    this->initGLEW();

    std::cout << "Seems we made it " << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void FullScreenApplication::shutDown(int return_code) {
    glfwTerminate();
    exit(return_code);
}

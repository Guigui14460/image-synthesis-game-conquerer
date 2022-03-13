#include "BackgroundRenderer.hpp"
#include <random>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "BasicObjects.hpp"

BackgroundRenderer::BackgroundRenderer(uint numberOfStars)
    : m_program("conquerer/3d.v.glsl", "conquerer/3d.f.glsl"), m_view(1), m_currentTime(0), m_deltaTime(0),
      m_eyePhi(PI / 8), m_eyeTheta(PI / 2 + PI / 10) {
    GLFWwindow* window = glfwGetCurrentContext();
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    this->resize(window, windowWidth, windowHeight);
    this->initGLState();
    this->createVAO(numberOfStars);
}

void BackgroundRenderer::initGLState() const {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void BackgroundRenderer::createVAO(uint numberOfStars) {
    m_vao = BasicObjects::makeSphere(20, 20, glm::vec3(1.f));
    // initialize meshes
    std::vector<glm::vec3> points = this->generateRandomStars(numberOfStars);
    std::vector<float> sizes = this->generateRandomSizes(numberOfStars, 0.004, 0.001);
    for(uint i = 0; i < numberOfStars; i++){
        this->m_meshes.push_back(std::shared_ptr<Mesh>(new Mesh(m_vao, points[i], points[i], glm::vec3(0.f), glm::vec3(sizes[i]))));
    }
}

void BackgroundRenderer::renderFrame()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->m_program.bind();

//    m_view = glm::mat4(1);

    for(auto& vao: this->m_meshes){
        vao->updateProgram(this->m_program, m_proj, m_view);
        vao->render();
    }

  this->m_program.unbind();
}

void BackgroundRenderer::update(bool activateContinuousKeys) {
    float prevTime = this->m_currentTime;
    this->m_currentTime = glfwGetTime();
    this->m_deltaTime = this->m_currentTime - prevTime;

    if(activateContinuousKeys){
        this->continuousKey();
    }
    // camera (create an object to handle that) -> not working here
    glm::vec3 center(0, 0, 0);
    glm::vec3 up(1, 0, 0);
    glm::vec3 eyePos = 5.f * glm::vec3(glm::cos(glm::radians(m_eyePhi)) * glm::sin(glm::radians(m_eyeTheta)), glm::sin(glm::radians(m_eyePhi)) * glm::sin(glm::radians(m_eyeTheta)), glm::cos(glm::radians(m_eyeTheta)));
    m_view = glm::lookAt(center, eyePos, up);

    this->m_program.bind();
//    this->m_program.setUniform("time", this->m_currentTime);
    this->m_program.unbind();

    for (auto& vao : this->m_meshes) {
      vao->update(this->m_deltaTime);
    }
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

std::vector<glm::vec3> BackgroundRenderer::generateRandomStars(uint numberOfStars) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(MIN_ANGLE_BACKGROUND, MAX_ANGLE_BACKGROUND);

    float phi, theta;
    std::vector<glm::vec3> points(numberOfStars);
    for(uint i = 0; i < numberOfStars; i++){
        phi = distr(eng); theta = distr(eng);
        points[i].x = glm::cos(theta) * glm::sin(phi);
        points[i].y = glm::sin(theta) * glm::sin(phi);
        points[i].z = glm::cos(phi);
    }

    return points;
}

std::vector<float> BackgroundRenderer::generateRandomSizes(uint numberOfStars, float min, float max) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(min, max);

    std::vector<float> sizes(numberOfStars);
    for(uint i = 0; i < numberOfStars; i++){
        sizes[i] = distr(eng);
    }

    return sizes;
}

void BackgroundRenderer::continuousKey() {
    GLFWwindow * window = glfwGetCurrentContext();
    const float pi = glm::pi<float>();
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        m_eyeTheta += m_deltaTime * pi * 10;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_eyeTheta -= m_deltaTime * pi * 10;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_eyePhi += m_deltaTime * pi * 10;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_eyePhi -= m_deltaTime * pi * 10;
    }
}

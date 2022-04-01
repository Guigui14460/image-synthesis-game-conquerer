#include "BackgroundRenderer.hpp"
#include <random>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "BasicObjects.hpp"

BackgroundRenderer::BackgroundRenderer(uint numberOfStars)
    : m_program("conquerer/3d.v.glsl", "conquerer/3d.f.glsl"), m_proj(1), m_view(1),
      m_camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)),
      m_currentTime(0), m_deltaTime(0) {
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
        this->m_meshes.push_back(std::make_shared<Mesh>(m_vao, points[i], points[i], glm::vec3(0.f), glm::vec3(sizes[i])));
    }
}

void BackgroundRenderer::renderFrame()
{
    this->m_program.bind();

    for(auto& mesh: this->m_meshes){
        mesh->render(this->m_program, m_proj * m_view);
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

    this->m_view = this->m_camera.calculateViewMatrix();

    for (auto& mesh : this->m_meshes) {
        mesh->update(this->m_deltaTime);
    }
}

constexpr float ANGLE_TO_ROTATE = 30.f;

void BackgroundRenderer::continuousKey() {
    GLFWwindow * window = glfwGetCurrentContext();
    float theta = 0, phi = 0;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        theta -= ANGLE_TO_ROTATE;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        theta += ANGLE_TO_ROTATE;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        phi -= ANGLE_TO_ROTATE;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        phi += ANGLE_TO_ROTATE;
    }
    this->m_camera.rotate(this->m_deltaTime, glm::vec2(phi, theta));
}



void BackgroundRenderer::resize(GLFWwindow*, int frameBufferWidth, int frameBufferHeight)
{
    this->m_proj = this->m_camera.calculateProjectionMatrix(90.f, frameBufferWidth, frameBufferHeight, 0.1f, 100.f);
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

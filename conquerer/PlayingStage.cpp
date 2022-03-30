#include "PlayingStage.hpp"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

constexpr float ANGLE_TO_ROTATE = 40.f;

PlayingStage::PlayingStage(const std::shared_ptr<Renderer>& renderer): m_renderer(renderer) {}

PlayingStage::~PlayingStage() {}

void PlayingStage::renderFrame() {
    this->m_renderer->renderFrame();
}

void PlayingStage::update() {
    this->continuousKey();
    this->m_renderer->update();
}

void PlayingStage::resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) {
    this->m_renderer->resize(window, frameBufferWidth, frameBufferHeight);
}

void PlayingStage::continuousKey() {
    GLFWwindow* window = glfwGetCurrentContext();
    glm::vec2 player1CameraAngles(0), player2CameraAngles(0);

    // player 1 keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player1CameraAngles.x -= ANGLE_TO_ROTATE;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player1CameraAngles.x += ANGLE_TO_ROTATE;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player1CameraAngles.y -= ANGLE_TO_ROTATE;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player1CameraAngles.y += ANGLE_TO_ROTATE;
    }

    // player 2 keys
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        player2CameraAngles.x -= ANGLE_TO_ROTATE;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        player2CameraAngles.x += ANGLE_TO_ROTATE;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        player2CameraAngles.y -= ANGLE_TO_ROTATE;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        player2CameraAngles.y += ANGLE_TO_ROTATE;
    }

    this->m_renderer->cameraAnglesUpdate(player1CameraAngles, player2CameraAngles);
}

void PlayingStage::keyCallback(GLFWwindow*, int /* key */, int, int /* action */, int) {}

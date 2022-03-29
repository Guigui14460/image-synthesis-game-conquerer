#include "PlayingStage.hpp"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

constexpr float ANGLE_TO_ROTATE = 10.f;

PlayingStage::PlayingStage(const std::shared_ptr<Renderer>& renderer): m_renderer(renderer) {}

PlayingStage::~PlayingStage() {}

void PlayingStage::renderFrame() {
    this->m_renderer->renderFrame();
}

void PlayingStage::update() {
    this->m_renderer->update();
}

void PlayingStage::resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) {
    this->m_renderer->resize(window, frameBufferWidth, frameBufferHeight);
}

void PlayingStage::keyCallback(GLFWwindow*, int key, int, int action, int) {
    glm::vec2 player1CameraAngles(0), player2CameraAngles(0);
    if(action == GLFW_PRESS) {
        switch(key) {
        case GLFW_KEY_Z:
            player1CameraAngles.y -= ANGLE_TO_ROTATE;
            break;
        case GLFW_KEY_S:
            player1CameraAngles.y += ANGLE_TO_ROTATE;
            break;
        case GLFW_KEY_Q:
            player1CameraAngles.x += ANGLE_TO_ROTATE;
            break;
        case GLFW_KEY_D:
            player1CameraAngles.x -= ANGLE_TO_ROTATE;
            break;
        case GLFW_KEY_UP:
            player2CameraAngles.y -= ANGLE_TO_ROTATE;
            break;
        case GLFW_KEY_DOWN:
            player2CameraAngles.y += ANGLE_TO_ROTATE;
            break;
        case GLFW_KEY_LEFT:
            player2CameraAngles.x += ANGLE_TO_ROTATE;
            break;
        case GLFW_KEY_RIGHT:
            player2CameraAngles.x -= ANGLE_TO_ROTATE;
            break;
        }
    }

    this->m_renderer->cameraAnglesUpdate(player1CameraAngles, player2CameraAngles);
}

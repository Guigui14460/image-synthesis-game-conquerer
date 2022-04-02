#include "EndStage.hpp"
#include <unordered_map>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

EndStage::EndStage(const std::shared_ptr<Renderer>& renderer)
    : m_renderer(renderer) {
    int frameBufferWidth, frameBufferHeight;
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

    std::unordered_map<PlayerObject::player_t, std::string> map;
    map[PlayerObject::COMPUTER] = "Computer";
    map[PlayerObject::PLAYER1] = "Player 1";
    map[PlayerObject::PLAYER2] = "Player 2";

    this->m_text = std::unique_ptr<TextPrinter>(new TextPrinter(frameBufferWidth, frameBufferHeight));
    const glm::vec3 red(1, 0, 0);
    const glm::vec3 blue(0, 0.3, 1);
    this->m_text->printText("gameover", "WINNER:", 2, 6, 9, red);
    this->m_text->printText("winner", map[renderer->getWinner()], 1, 7.5, 10, blue);
}

void EndStage::renderFrame() {
    this->m_renderer->renderFrame();
    this->m_text->draw();
}

void EndStage::update() {
    this->m_renderer->update();
}

void EndStage::resize(GLFWwindow *window, int frameBufferWidth, int frameBufferHeight) {
    this->m_renderer->resize(window, frameBufferWidth, frameBufferHeight);
    this->m_text->resize(frameBufferWidth, frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

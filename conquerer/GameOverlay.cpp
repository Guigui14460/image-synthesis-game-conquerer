#include "GameOverlay.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "GameLogic.hpp"
#include "BasicObjects.hpp"

GameOverlay::GameOverlay(int frameBufferWidth, int frameBufferHeight)
    : m_textRenderer(new TextPrinter(frameBufferWidth, frameBufferHeight)),
      m_program(new Program("conquerer/2d.v.glsl", "conquerer/2d.f.glsl")),
      m_leftTime(MAX_GAME_DURATION), m_baseColor(0.9098f, 0.89412f, 0.8902f),
      m_needUpdateChrono(true) {
    this->createVAOs();
}

void GameOverlay::createVAOs() {
    // black bg
    std::vector<glm::vec2> positions = {{-.22, 1}, {-.22, .75}, {.22, .75}, {.22, 1}};
    this->m_vaos.push_back(BasicObjects::makeUniformSquare(positions, {0., 0., 0.}));

    // large vertical separator
    std::vector<glm::vec2> positions1 = {{-.02, .75}, {-.02, -1}, {.02, -1}, {.02, .75}};
    this->m_vaos.push_back(BasicObjects::makeUniformSquare(positions1, this->m_baseColor));

    // horizontal
    std::vector<glm::vec2> positions2 = {{-.25, .75}, {-.25, .7}, {.25, .7}, {.25, .75}};
    this->m_vaos.push_back(BasicObjects::makeUniformSquare(positions2, this->m_baseColor));

    // left timer separator
    std::vector<glm::vec2> positions3 = {{-.25, 1}, {-.25, .7}, {-.22, .7}, {-.22, 1}};
    this->m_vaos.push_back(BasicObjects::makeUniformSquare(positions3, this->m_baseColor));

    // right timer separator
    std::vector<glm::vec2> positions4 = {{.22, 1}, {.22, .7}, {.25, .7}, {.25, 1}};
    this->m_vaos.push_back(BasicObjects::makeUniformSquare(positions4, this->m_baseColor));
}

void GameOverlay::update(float /* deltaTime */) {
    if(m_needUpdateChrono) {
        std::string string;
        string += std::to_string(this->m_leftTime / 60);
        string += ":";
        if(this->m_leftTime % 60 < 10) string += "0";
        string += std::to_string(this->m_leftTime % 60);

        glm::vec3 color = this->m_baseColor;
        if(this->m_leftTime <= 30) color = {0.95882f, 0.31961f, 0.24118f};
        this->m_textRenderer->printText("timer", string, 5.1, 0.5, 7, color, {0, 0, 0, 1});
        m_needUpdateChrono = false;
    }
}

void GameOverlay::draw() {
    this->m_textRenderer->draw();

    this->m_program->bind();
    for(std::shared_ptr<VAO> vao: this->m_vaos) {
        vao->draw();
    }
    this->m_program->unbind();
}

void GameOverlay::resize(int frameBufferWidth, int frameBufferHeight) {
    this->m_textRenderer->resize(frameBufferWidth, frameBufferHeight);
}

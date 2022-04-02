#ifndef __GAME_OVERLAY_HPP__
#define __GAME_OVERLAY_HPP__
#include <glm/vec3.hpp>
#include "TextPrinter.hpp"
#include "glApi.hpp"

/**
 * @brief The GameOverlay class represents the overlay of the playing stage
 */
class GameOverlay {
public:
    /// Default constructor
    GameOverlay(int frameBufferWidth, int frameBufferHeight);
    GameOverlay(const GameOverlay& o) = delete;

    /// Update the overlay
    void update(float deltaTime);

    /// Draws the 2D overlay
    void draw();

    /**
     * @brief Resizes the viewport stored in the TextPrinter object
     * @param frameBufferWidth width of the viewport
     * @param frameBufferHeight height of the viewport
     */
    void resize(int frameBufferWidth, int frameBufferHeight);

    inline void setLeftTime(float leftTime) {
        this->m_leftTime = static_cast<int>(leftTime);
        this->m_needUpdateChrono = true;
    }

private:
    /// creates the separator
    void createVAOs();

private:
    std::unique_ptr<TextPrinter> m_textRenderer; /// to render texts
    std::vector<std::shared_ptr<VAO>> m_vaos;
    std::unique_ptr<Program> m_program;
    int m_leftTime; /// left time to show on the screen
    glm::vec3 m_baseColor;
    bool m_needUpdateChrono; /// check if we need to update VAO chrono text
};

#endif // __GAME_OVERLAY_HPP__

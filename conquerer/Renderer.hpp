#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include "glApi.hpp"
#include "Camera.hpp"
#include "GameLogic.hpp"
#include "BackgroundRenderer.hpp"
#include "GameOverlay.hpp"
#include "PlayerObject.hpp"

/// structure to easily manipulate camera player objects
struct camera_t {
    Camera camera;
    glm::vec2 angles;
    camera_t(Camera cam, glm::vec2 ang) : camera(cam), angles(ang) {}
};

class Renderer {
public:
    enum renderer_part_t {LEFT_PART, RIGHT_PART};

    Renderer() = delete;
    Renderer(const Renderer& o) = default;

    /// Constructor
    Renderer(int frameBufferWidth, int frameBufferHeight, float universeRadius, bool leftPartIsPlayer1);

    /**
     * @brief Resizes the render screen to fit with the GLFW window screen size.
     * @param window the GLFW window object
     * @param frameBufferWidth the new width of the frame buffer to display
     * @param frameBufferHeight the new height of the frame buffer to display
     */
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);

    /// Renders a single frame to the screen.
    void renderFrame();

    /// Updates the time related objects.
    void update();

    /// Updates the cameras angles of the two players
    void cameraAnglesUpdate(glm::vec2& player1CameraAngles, glm::vec2& player2CameraAngles);

    void startGame();
    bool isFinished() { return this->m_logic->isFinished(); }
    bool isStarted() { return this->m_logic->isLaunched(); }
    PlayerObject::player_t getWinner() { return this->m_logic->getWinner(); }

private:
    /// Render part of the screen
    void renderPart(renderer_part_t part);

    /// OpenGL state initialization
    void initGLState() const;

    void initGameLogic(float universeRadius, const glm::vec3& origin);
    
    /**
     * @brief calculPositionPlanet
     * @return a vertex in 3 dimension for planet's position
     */
    glm::vec3 calculPositionPlanet();

    /**
     * @brief calculPlacementObject
     * @return a 3 dimension's vertex for player object's position
     */
    glm::vec3 calculPlacementObject(glm::vec3 vertPlanet);

private:
    std::shared_ptr<PlayerObject> m_player1_object;
    std::shared_ptr<PlayerObject> m_player2_object;
    std::shared_ptr<PlanetObject> m_target;
    float m_universeRadius;

    camera_t m_cameraPlayer1, m_cameraPlayer2;
    std::shared_ptr<GameLogic> m_logic;
    BackgroundRenderer m_background;
    GameOverlay m_overlay;
    float m_currentTime, m_deltaTime;
    bool m_leftPartIsPlayer1;
    int m_frameBufferWidth; /// The width of the current viewport
    int m_frameBufferHeight; /// The height of the current viewport
    float m_timeCounter;
};

#endif // __RENDERER_HPP__

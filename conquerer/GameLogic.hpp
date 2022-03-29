#ifndef __GAME_LOGIC_HPP__
#define __GAME_LOGIC_HPP__
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "AbstractGameObject.hpp"
#include "PlayerObject.hpp"
#include "AsteroidObject.hpp"
#include "PlanetObject.hpp"
#include "ProjectileObject.hpp"

#define MAX_GAME_DURATION 180.f
#define MIN_CAPTURE_PLANET_DURATION 10.f
#define MAX_AVAILABLE_RADIUS_FOR_PLAYER 0.9f

/**
 * @brief The GameLogic class represents all the logic of the Conquerer game
 */
class GameLogic {
public:
    /// Constructor
    GameLogic(std::shared_ptr<PlayerObject>& player1, std::shared_ptr<PlayerObject>& player2,
              std::shared_ptr<PlanetObject>& target, std::vector<std::shared_ptr<AsteroidObject>>& asteroids,
              std::vector<std::shared_ptr<PlanetObject>>& planets, const float universeRadius);

    /**
     * @brief Launches the logic of the game
     * @param beginTime time of the beggining of the game
     */
    void launch(double beginTime);

    /// Updates objects in the environment
    void updateObjects(double actualTime);

    /// Adds a projectile to the projectiles vector
    void addProjectile(const std::shared_ptr<ProjectileObject>& o);

    /**
     * @brief Gets the left time of the current game
     * @param actualTime the current window time
     * @return the left time
     */
    double getLeftTime(double actualTime);

    /**
     * @brief Gets left capture time
     * @param actualTime the current window time
     * @return the left time for capturing target by ennemy
     */
    double getLeftCaptureTime(double actualTime);

    /// Checks if the game is finished or not
    bool isFinished();

    /// Checks if a capture has began
    bool isTargetCaptureBegan();

    /// Gets the winner of the game
    PlayerObject::player_t getWinner();

    /// Gets the current capturer
    PlayerObject::player_t getCapturer();

    /// Returns a vector of game objects (for rendering, etc)
    std::vector<std::shared_ptr<AbstractGameObject>> getGameObjects();

    std::vector<std::shared_ptr<AsteroidObject>> getAsteroidObjects() { return this->m_asteroids; }
    std::vector<std::shared_ptr<PlanetObject>> getPlanetObjects() { return this->m_planets; }
    std::vector<std::shared_ptr<ProjectileObject>> getProjectileObjects() { return this->m_projectiles; }
    std::shared_ptr<PlanetObject> getTargetPlanet() { return this->m_targetPlanet; }

    /// Returns player objects (first is the PLAYER1 and second the PLAYER2
    std::vector<std::shared_ptr<PlayerObject>> getPlayers() {
        std::vector<std::shared_ptr<PlayerObject>> vec(2);

        if(this->m_player1->getPlayerType() == PlayerObject::PLAYER1)
            vec[0] = this->m_player1;
        else
            vec[0] = this->m_player2;

        if(this->m_player1->getPlayerType() == PlayerObject::PLAYER2)
            vec[1] = this->m_player1;
        else
            vec[1] = this->m_player2;

        return vec;
    }

private:
    /// Checks all collisions between objects
    void checkCollisions();

    /// Removes useless objects from the environment
    void removeUselessObjects();

private:
    std::shared_ptr<PlayerObject>& m_player1, m_player2;
    std::shared_ptr<PlanetObject>& m_targetPlanet;
    std::vector<std::shared_ptr<AsteroidObject>>& m_asteroids;
    std::vector<std::shared_ptr<PlanetObject>>& m_planets;
    std::vector<std::shared_ptr<ProjectileObject>> m_projectiles;
    PlayerObject::player_t m_winner;
    PlayerObject::player_t m_capturer = PlayerObject::NONE;
    double m_beginTime = -1.f, m_beginCapturePlanet = -1.f;
    bool m_beginCapture = false;
    const float m_universeRadius;
};

#endif // __GAME_LOGIC_HPP__

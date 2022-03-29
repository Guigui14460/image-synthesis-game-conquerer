#ifndef __GAME_LOGIC_HPP__
#define __GAME_LOGIC_HPP__
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include "AbstractGameObject.hpp"

class GameLogic {
public:
    GameLogic();

    void updateObjects();
    void checkCollisions();
    void deleteObject(AbstractGameObject& o);

    float getLeftTime(float actualTime);
    bool isFinished();


private:
    glm::vec3 m_positionPlayer1, m_positionPlayer2;
    glm::vec2 m_directionPlayer1, m_directionPlayer2;
    // TODO: or Player m_player1, m_player2;
    float m_beginTime;
//    std::shared_ptr<Planet> m_targetPlanet;
//    std::vector<std::shared_ptr<Asteroid>> m_asteroids;
//    std::vector<std::shared_ptr<Planet>> m_planets;
    bool m_finished;
    // Player m_winner;
};

#endif // __GAME_LOGIC_HPP__

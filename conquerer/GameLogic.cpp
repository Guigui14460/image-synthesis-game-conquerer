#include "GameLogic.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <glm/geometric.hpp>

GameLogic::GameLogic(std::shared_ptr<PlayerObject>& player1, std::shared_ptr<PlayerObject>& player2,
                     std::shared_ptr<PlanetObject>& target, std::vector<std::shared_ptr<AsteroidObject>>& asteroids,
                     std::vector<std::shared_ptr<PlanetObject>>& planets, const float universeRadius, const glm::vec3& origin)
    : m_player1(player1), m_player2(player2), m_targetPlanet(target),
      m_asteroids(asteroids), m_planets(planets), m_winner(PlayerObject::NONE), m_universeRadius(universeRadius), m_origin(origin) {
}

void GameLogic::launch(float beginTime) {
    this->m_beginTime = beginTime;
}

void GameLogic::updateObjects(float actualTime) {
    if(this->isFinished()) return;

    // if current capturer has captured the target planet
    if(this->isTargetCaptureBegan() and this->getLeftCaptureTime(actualTime) == 0) {
        this->m_winner = this->m_capturer;
        return;
    }

//    if(glm::distance(this->m_player1->getPosition(), m_origin) >= MAX_AVAILABLE_RADIUS_FOR_PLAYER * this->m_universeRadius) {
//        this->m_player1->inverseOrientation();
//    }
//    if(glm::distance(this->m_player2->getPosition(), m_origin) >= MAX_AVAILABLE_RADIUS_FOR_PLAYER * this->m_universeRadius) {
//        this->m_player2->inverseOrientation();
//    }

    this->removeUselessObjects();
    this->checkCollisions();

    // checks if a player is in the target planet
    bool p1InTarget = this->m_player1->isCollided(*this->m_targetPlanet.get());
    bool p2InTarget = this->m_player2->isCollided(*this->m_targetPlanet.get());
    if(this->m_capturer == PlayerObject::NONE) {
        if(p1InTarget and p2InTarget) {
            if(this->m_player1->getHealth() == this->m_player2->getHealth()) {
                this->m_winner = PlayerObject::COMPUTER; // equality
            } else if(this->m_player1->getHealth() > this->m_player2->getHealth()) {
                this->m_winner = this->m_player1->getPlayerType();
            } else {
                this->m_winner = this->m_player2->getPlayerType();
            }
        } else if(p1InTarget) {
            this->m_capturer = this->m_player1->getPlayerType();
            this->m_beginCapture = actualTime;
        } else if(p2InTarget) {
            this->m_capturer = this->m_player2->getPlayerType();
            this->m_beginCapture = actualTime;
        }
    } else if(this->m_capturer == this->m_player1->getPlayerType()) {
        if(p2InTarget and this->m_targetPlanet->getHealth() < this->m_player2->getHealth()) {
            this->m_winner = this->m_player2->getPlayerType();
        } else if (p2InTarget) {
            this->m_winner = this->m_player1->getPlayerType();
        }
    } else if(this->m_capturer == this->m_player2->getPlayerType()) {
        if(p1InTarget and this->m_targetPlanet->getHealth() < this->m_player1->getHealth()) {
            this->m_winner = this->m_player1->getPlayerType();
        } else if (p1InTarget) {
            this->m_winner = this->m_player2->getPlayerType();
        }
    }

    // time over without winner
    if(this->getLeftTime(actualTime) == 0 and this->m_winner == PlayerObject::NONE) {
        if(m_player1->isDestroyed() and m_player2->isDestroyed()) {
            this->m_winner = PlayerObject::COMPUTER;
        } else if(m_player1->isDestroyed()){
            this->m_winner = this->m_player2->getPlayerType();
        } else if(m_player2->isDestroyed()){
            this->m_winner = this->m_player1->getPlayerType();
        } else { // no more left time
            this->m_winner = PlayerObject::COMPUTER;
        }
    }
}

void GameLogic::checkCollisions() {
    float playerHealth, objectHealth;
    std::vector<std::shared_ptr<AbstractGameObject>> objectsToRemove;
    std::shared_ptr<AbstractGameObject> o;

    for(size_t i = 0; i < this->m_projectiles.size(); i++) {
        o = this->m_projectiles[i];
        objectHealth = o->getHealth();
        if(this->m_targetPlanet->isCollided(*o.get())) { // planet-projectile collisions
            if(this->m_capturer != PlayerObject::NONE) {
                this->m_targetPlanet->removeHealth(objectHealth);
            }
            o->removeHealth(objectHealth);
        } else { // player-plrojectile collisions
            if(this->m_player1->isCollided(*o.get())) {
                playerHealth = this->m_player1->getHealth();
                this->m_player1->removeHealth(objectHealth);
                o->removeHealth(playerHealth);
            }
            if(this->m_player2->isCollided(*o.get())) {
                playerHealth = this->m_player1->getHealth();
                this->m_player2->removeHealth(objectHealth);
                o->removeHealth(playerHealth);
            }
        }

        if(o->isDestroyed()){
            objectsToRemove.push_back(o);
        }
    }
    this->m_projectiles.erase(std::remove_if(this->m_projectiles.begin(), this->m_projectiles.end(),
                                [&objectsToRemove](std::shared_ptr<ProjectileObject>& o) {
                     return std::count(objectsToRemove.begin(), objectsToRemove.end(), o);
                 }), this->m_projectiles.end());

    objectsToRemove.clear();
    for(size_t i = 0; i < this->m_asteroids.size(); i++) { // player-asteroids collisions
        o = this->m_asteroids[i];
        objectHealth = o->getHealth();
        if(this->m_player1->isCollided(*o.get())) {
            playerHealth = this->m_player1->getHealth();
            this->m_player1->removeHealth(objectHealth);
            o->removeHealth(playerHealth);
        }
        if(this->m_player2->isCollided(*o.get())) {
            playerHealth = this->m_player1->getHealth();
            this->m_player2->removeHealth(objectHealth);
            o->removeHealth(playerHealth);
        }

        if(o->isDestroyed()){
            objectsToRemove.push_back(o);
        }
    }
    this->m_asteroids.erase(std::remove_if(this->m_asteroids.begin(), this->m_asteroids.end(),
                                [&objectsToRemove](std::shared_ptr<AsteroidObject>& o) {
                     return std::count(objectsToRemove.begin(), objectsToRemove.end(), o);
                 }), this->m_asteroids.end());

    objectsToRemove.clear();
    for(size_t i = 0; i < this->m_planets.size(); i++) { // player-planets collisions
        o = this->m_planets[i];
        objectHealth = o->getHealth();
        if(this->m_player1->isCollided(*o.get())) {
            playerHealth = this->m_player1->getHealth();
            this->m_player1->removeHealth(objectHealth);
            o->removeHealth(playerHealth);
        }
        if(this->m_player2->isCollided(*o.get())) {
            playerHealth = this->m_player1->getHealth();
            this->m_player2->removeHealth(objectHealth);
            o->removeHealth(playerHealth);
        }

        if(o->isDestroyed()){
            objectsToRemove.push_back(o);
        }
    }
    this->m_planets.erase(std::remove_if(this->m_planets.begin(), this->m_planets.end(),
                                [&objectsToRemove](std::shared_ptr<PlanetObject>& o) {
                     return std::count(objectsToRemove.begin(), objectsToRemove.end(), o);
                 }), this->m_planets.end());

    if(this->m_player1->isCollided(*this->m_player2.get())){ // player-player collision
        float p1Health = this->m_player1->getHealth();
        float p2Health = this->m_player2->getHealth();
        if(p1Health == p2Health) {
            this->m_player1->removeHealth(p1Health);
            this->m_player2->removeHealth(p1Health);
            this->m_winner = PlayerObject::COMPUTER;
        } else if(p1Health > p2Health) {
            this->m_player1->removeHealth(p2Health);
            this->m_player2->removeHealth(p2Health);
            this->m_winner = this->m_player1->getPlayerType();
        } else if(p1Health < p2Health) {
            this->m_player1->removeHealth(p1Health);
            this->m_player2->removeHealth(p1Health);
            this->m_winner = this->m_player2->getPlayerType();
        }
    }
}

void GameLogic::removeUselessObjects() {
    std::vector<std::shared_ptr<AbstractGameObject>> objectsToRemove;
    std::shared_ptr<AbstractGameObject> o;

    for(size_t i = 0; i < this->m_projectiles.size(); i++) {
        o = this->m_projectiles[i];
        if(glm::distance(o->getPosition(), {0.f, 0.f, 0.f}) >= this->m_universeRadius) {
            objectsToRemove.push_back(o);
        }
    }
    this->m_projectiles.erase(std::remove_if(this->m_projectiles.begin(), this->m_projectiles.end(),
                                [&objectsToRemove](std::shared_ptr<ProjectileObject>& o) {
                     return std::count(objectsToRemove.begin(), objectsToRemove.end(), o);
                 }), this->m_projectiles.end());
}

float GameLogic::getLeftTime(float actualTime) {
    double value = actualTime - (this->m_beginTime + MAX_GAME_DURATION);
    if(value >= 0){
        value = 0;
    }
    return value;
}

float GameLogic::getLeftCaptureTime(float actualTime) {
    double value = actualTime - (this->m_beginCapturePlanet + MIN_CAPTURE_PLANET_DURATION);
    if(value >= 0){
        value = 0;
    }
    return value;
}

bool GameLogic::isFinished() {
    return this->m_winner != PlayerObject::NONE;
}

bool GameLogic::isTargetCaptureBegan() {
    return this->m_capturer != PlayerObject::NONE;
}

PlayerObject::player_t GameLogic::getWinner() {
    return this->m_winner;
}

PlayerObject::player_t GameLogic::getCapturer() {
    return this->m_capturer;
}

std::vector<std::shared_ptr<AbstractGameObject>> GameLogic::getGameObjects() {
    std::vector<std::shared_ptr<AbstractGameObject>> vec;

    vec.push_back(this->m_player1);
    vec.push_back(this->m_player2);
    vec.push_back(this->m_targetPlanet);

    vec.reserve(vec.size() + std::distance(this->m_asteroids.begin(), this->m_asteroids.end()));
    vec.insert(vec.end(), this->m_asteroids.begin(), this->m_asteroids.end());

    vec.reserve(vec.size() + std::distance(this->m_planets.begin(), this->m_planets.end()));
    vec.insert(vec.end(), this->m_planets.begin(), this->m_planets.end());

    vec.reserve(vec.size() + std::distance(this->m_projectiles.begin(), this->m_projectiles.end()));
    vec.insert(vec.end(), this->m_projectiles.begin(), this->m_projectiles.end());

    return vec;
}

void GameLogic::addProjectile(const std::shared_ptr<ProjectileObject>& o) {
    this->m_projectiles.push_back(o);
}

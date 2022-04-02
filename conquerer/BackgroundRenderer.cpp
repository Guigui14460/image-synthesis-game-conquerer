#include "BackgroundRenderer.hpp"
#include <random>
#include "BasicObjects.hpp"

BackgroundRenderer::BackgroundRenderer(uint numberOfStars, float universeRadius, const glm::vec3& origin) {
    this->createVAO(numberOfStars, universeRadius, origin);
}

void BackgroundRenderer::createVAO(uint numberOfStars, float universeRadius, const glm::vec3& origin) {
    // initialize meshes
    std::vector<glm::vec3> points = this->generateRandomStars(numberOfStars, universeRadius);
    std::vector<float> sizes = this->generateRandomSizes(numberOfStars, 0.004, 0.001);
    for(uint i = 0; i < numberOfStars; i++){
        this->m_stars.push_back(std::shared_ptr<PlanetObject>(new PlanetObject(0, points[i], origin, glm::vec3(0.f), glm::vec3(sizes[i]), glm::vec3(1.f), 1.f)));
    }
}

void BackgroundRenderer::renderFrame(const glm::mat4 & view, const glm::mat4 & projection)
{
    for(auto& star: this->m_stars){
        star->draw(view, projection);
    }
}

void BackgroundRenderer::update(float deltaTime) {
    for (auto& star : this->m_stars) {
        star->update(deltaTime);
    }
}

std::vector<glm::vec3> BackgroundRenderer::generateRandomStars(uint numberOfStars, float universeRadius) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(MIN_ANGLE_BACKGROUND, MAX_ANGLE_BACKGROUND);

    float phi, theta;
    std::vector<glm::vec3> points(numberOfStars);
    for(uint i = 0; i < numberOfStars; i++){
        phi = distr(eng); theta = distr(eng);
        points[i].x = universeRadius * glm::cos(theta) * glm::sin(phi);
        points[i].y = universeRadius * glm::sin(theta) * glm::sin(phi);
        points[i].z = universeRadius * glm::cos(phi);
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

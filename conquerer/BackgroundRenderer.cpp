#include "BackgroundRenderer.hpp"
#include <random>
#include "BasicObjects.hpp"

BackgroundRenderer::BackgroundRenderer(uint numberOfStars, float universeRadius)
    : m_program("conquerer/3d.v.glsl", "conquerer/3d.f.glsl") {
    this->createVAO(numberOfStars, universeRadius);
}

void BackgroundRenderer::createVAO(uint numberOfStars, float universeRadius) {
    m_vao = BasicObjects::makeSphere(20, 20, glm::vec3(1.f));
    // initialize meshes
    std::vector<glm::vec3> points = this->generateRandomStars(numberOfStars, universeRadius);
    std::vector<float> sizes = this->generateRandomSizes(numberOfStars, 0.004, 0.001);
    for(uint i = 0; i < numberOfStars; i++){
        this->m_meshes.push_back(std::make_shared<Mesh>(m_vao, points[i], points[i], glm::vec3(0.f), glm::vec3(sizes[i])));
    }
}

<<<<<<< HEAD
void BackgroundRenderer::renderFrame(const glm::mat4 & view, const glm::mat4 & projection)
=======
void BackgroundRenderer::renderFrame(const glm::mat4& projViewMatrix)
>>>>>>> origin/game_logic
{
    this->m_program.bind();

    for(auto& mesh: this->m_meshes){
<<<<<<< HEAD
<<<<<<< HEAD
        mesh->render(this->m_program, view, projection);
=======
        mesh->updateProgram(this->m_program, projViewMatrix);
        mesh->render();
>>>>>>> origin/game_logic
=======
        mesh->render(this->m_program, this->m_camera.getViewMatrix(), this->m_camera.getProjectionMatrix());
>>>>>>> 76756a395e3f6928abbc77ab9f71bd0850d401ab
    }

    this->m_program.unbind();
}

<<<<<<< HEAD
void BackgroundRenderer::update(float deltaTime) {
=======
void BackgroundRenderer::update(float deltaTime, bool activateContinuousKeys) {
    float prevTime = this->m_currentTime;
    this->m_currentTime = glfwGetTime();
    this->m_deltaTime = this->m_currentTime - prevTime;

    if(activateContinuousKeys){
        this->continuousKey();
    }

    this->m_view = this->m_camera.calculateViewMatrix();

>>>>>>> 76756a395e3f6928abbc77ab9f71bd0850d401ab
    for (auto& mesh : this->m_meshes) {
        mesh->update(deltaTime);
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

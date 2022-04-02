#include "Renderer.hpp"
#include <GLFW/glfw3.h>

Renderer::Renderer(int frameBufferWidth, int frameBufferHeight, float universeRadius, bool leftPartIsPlayer1) :
    m_cameraPlayer1(Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)), glm::vec2(0.f)),
    m_cameraPlayer2(Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)), glm::vec2(0.f)),
    m_background(250, universeRadius, glm::vec3(0.f)), m_overlay(frameBufferWidth, frameBufferHeight), m_currentTime(0), m_deltaTime(0),
    m_leftPartIsPlayer1(leftPartIsPlayer1), m_frameBufferWidth(frameBufferWidth), m_frameBufferHeight(frameBufferHeight) {
    this->initGLState();
    this->initGameLogic(universeRadius, glm::vec3(0.f));
}

void Renderer::initGLState() const {
    glClearColor(1.f, 0.f, 1.f, 1.f);
//    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::initGameLogic(float universeRadius, const glm::vec3& origin) {
    std::shared_ptr<Program> textureProgram = std::shared_ptr<Program>(new Program("conquerer/texture.v.glsl", "conquerer/texture.f.glsl"));
    std::shared_ptr<PlayerObject> player1 = PlayerObject::loadObjsPlayer(PlayerObject::PLAYER1, textureProgram, 100, glm::vec3(3.f), origin, glm::vec3(0.f), glm::vec3(1.f));
    std::shared_ptr<PlayerObject> player2 = PlayerObject::loadObjsPlayer(PlayerObject::PLAYER2, textureProgram, 100, glm::vec3(3.f), origin, glm::vec3(0.f), glm::vec3(1.f));
    std::shared_ptr<PlanetObject> target = std::shared_ptr<PlanetObject>(new PlanetObject(0, glm::vec3(0.f), origin, glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.f, 0.5f, 1.f), 0.5f));
    std::vector<std::shared_ptr<AsteroidObject>> asteroids;
    std::vector<std::shared_ptr<PlanetObject>> planets;
    m_player_object = player1;

    this->m_logic = std::shared_ptr<GameLogic>(new GameLogic(player1, player2, target, asteroids, planets, universeRadius, origin));
}

void Renderer::resize(GLFWwindow*, int frameBufferWidth, int frameBufferHeight) {
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    this->m_frameBufferWidth = frameBufferWidth;
    this->m_frameBufferHeight = frameBufferHeight;

    this->m_cameraPlayer1.camera.calculateProjectionMatrix(90., this->m_frameBufferWidth/2, this->m_frameBufferHeight, .1, 100.);
    this->m_cameraPlayer2.camera.calculateProjectionMatrix(90., this->m_frameBufferWidth/2, this->m_frameBufferHeight, .1, 100.);
}

void Renderer::update() {
    float prevTime = this->m_currentTime;
    this->m_currentTime = glfwGetTime();
    this->m_deltaTime = this->m_currentTime - prevTime;

    this->m_cameraPlayer1.camera.calculateViewMatrix();
    this->m_cameraPlayer2.camera.calculateViewMatrix();

    this->m_background.update(this->m_deltaTime);
    this->m_overlay.update(this->m_deltaTime);
}

void Renderer::cameraAnglesUpdate(glm::vec2& player1CameraAngles, glm::vec2& player2CameraAngles) {
    // TODO: update here the player orientation
    if(player1CameraAngles.x != 0 or player1CameraAngles.y != 0){
        this->m_cameraPlayer1.angles += player1CameraAngles;
        this->m_cameraPlayer1.camera.rotate(this->m_deltaTime, player1CameraAngles);
    }
    if(player2CameraAngles.x != 0 or player2CameraAngles.y != 0){
        this->m_cameraPlayer2.angles += player2CameraAngles;
        this->m_cameraPlayer2.camera.rotate(this->m_deltaTime, player2CameraAngles);
    }
}

void Renderer::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->renderPart(LEFT_PART);
    this->renderPart(RIGHT_PART);

    glViewport(0, 0, this->m_frameBufferWidth, this->m_frameBufferHeight);
    this->m_overlay.draw();
}

void Renderer::renderPart(renderer_part_t part) {
    camera_t cameraToUse = this->m_cameraPlayer1;
    int minX = 0;
    if(part == RIGHT_PART){
        minX = this->m_frameBufferWidth/2 + 1;
        cameraToUse = this->m_cameraPlayer2;
    }

    glViewport(minX, 0, this->m_frameBufferWidth/2, this->m_frameBufferHeight);

    this->m_background.renderFrame(cameraToUse.camera.getViewMatrix(), cameraToUse.camera.getProjectionMatrix());
    m_player_object->draw(cameraToUse.camera.getViewMatrix(), cameraToUse.camera.getProjectionMatrix());
    // TODO: render other game objects
}

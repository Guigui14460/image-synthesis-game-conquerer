#include "Renderer.hpp"
#include <GLFW/glfw3.h>
#include <random>
#include <math.h>

Renderer::Renderer(int frameBufferWidth, int frameBufferHeight, float universeRadius, bool leftPartIsPlayer1) :
    m_cameraPlayer1(Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)), glm::vec2(0.f)),
    m_cameraPlayer2(Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)), glm::vec2(0.f)),
    m_background(250, universeRadius, glm::vec3(0.f)), m_overlay(frameBufferWidth, frameBufferHeight), m_currentTime(0), m_deltaTime(0),
    m_leftPartIsPlayer1(leftPartIsPlayer1), m_frameBufferWidth(frameBufferWidth), m_frameBufferHeight(frameBufferHeight), m_timeCounter(0) {
    this->initGLState();
    this->initGameLogic(universeRadius, glm::vec3(0.f));
}

void Renderer::initGLState() const {
//    glClearColor(1.f, 0.f, 1.f, 1.f);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

glm::vec3 Renderer::calculPositionPlanet(){
    glm::vec3 val;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr1{0, m_universeRadius-10};

    float radiusMax= distr1(eng);

    std::uniform_real_distribution<> distr2{-radiusMax, radiusMax};

    val.x = distr2(eng);
    val.y = distr2(eng);
    val.z = distr2(eng);

    m_universeRadius-=radiusMax;

    return val;
}

glm::vec3 Renderer::calculPlacementObject(glm::vec3 vertPlanet){
    glm::vec3 vectPlay;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(0.f, 2.f * glm::pi<float>());

    float phi, theta;

    phi = distr(eng); theta = distr(eng);
    vectPlay.x = m_universeRadius * glm::cos(theta) * glm::sin(phi);
    vectPlay.y = m_universeRadius * glm::sin(theta) * glm::sin(phi);
    vectPlay.z = m_universeRadius * glm::cos(phi);

    return vectPlay + vertPlanet;
}

void Renderer::initGameLogic(float universeRadius, const glm::vec3& origin) {
    m_universeRadius = universeRadius;
    
    std::shared_ptr<Program> textureProgram = std::shared_ptr<Program>(new Program("conquerer/texture.v.glsl", "conquerer/texture.f.glsl"));
    
    glm::vec3 vertPlanet = Renderer::calculPositionPlanet();
    glm::vec3 vertPlay1 = Renderer::calculPlacementObject(vertPlanet);
    glm::vec3 vertPlay2 = Renderer::calculPlacementObject(vertPlanet);

    m_player1_object = PlayerObject::loadObjsPlayer(PlayerObject::PLAYER1, textureProgram, 100, glm::vec3(vertPlay1), origin, glm::vec3(0.f), glm::vec3(1.f));
    m_player2_object = PlayerObject::loadObjsPlayer(PlayerObject::PLAYER2, textureProgram, 100, glm::vec3(vertPlay2), origin, glm::vec3(0.f), glm::vec3(1.f));
    m_target = std::shared_ptr<PlanetObject>(new PlanetObject(0, glm::vec3(vertPlanet), origin, glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.f, 0.5f, 1.f), 0.5f));
	
	std::vector<std::shared_ptr<AsteroidObject>> asteroids;
    std::vector<std::shared_ptr<PlanetObject>> planets;

    this->m_logic = std::shared_ptr<GameLogic>(new GameLogic(m_player1_object, m_player2_object, m_target, asteroids, planets, universeRadius, origin));
}

void Renderer::resize(GLFWwindow*, int frameBufferWidth, int frameBufferHeight) {
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    this->m_frameBufferWidth = frameBufferWidth;
    this->m_frameBufferHeight = frameBufferHeight;

    this->m_cameraPlayer1.camera.calculateProjectionMatrix(90., this->m_frameBufferWidth/2, this->m_frameBufferHeight, .1, 100.);
    this->m_cameraPlayer2.camera.calculateProjectionMatrix(90., this->m_frameBufferWidth/2, this->m_frameBufferHeight, .1, 100.);
}

void Renderer::startGame() {
    this->m_logic->launch(this->m_timeCounter);
}

void Renderer::update() {
    float prevTime = this->m_currentTime;
    this->m_currentTime = glfwGetTime();
    this->m_deltaTime = this->m_currentTime - prevTime;
    this->m_timeCounter += this->m_deltaTime;

    this->m_logic->updateObjects(this->m_deltaTime);

    this->m_overlay.setLeftTime(this->m_logic->getLeftTime(this->m_timeCounter));

    this->m_player1_object->update(this->m_deltaTime);
    this->m_player2_object->update(this->m_deltaTime);

    glm::vec3 positionP1 = this->m_player1_object->getPosition();
    glm::vec3 positionP2 = this->m_player2_object->getPosition();

    this->m_cameraPlayer1.camera.setPosition(positionP1 + glm::vec3(0,0.5,-0.3)) ;
    this->m_cameraPlayer2.camera.setPosition(positionP2 + glm::vec3(0,0.4,-0.2)) ;

    this->m_cameraPlayer1.camera.calculateViewMatrix();
    this->m_cameraPlayer2.camera.calculateViewMatrix();

    this->m_background.update(this->m_deltaTime);
    this->m_overlay.update(this->m_deltaTime);
}

void Renderer::cameraAnglesUpdate(glm::vec2& player1CameraAngles, glm::vec2& player2CameraAngles) {

    if(player1CameraAngles.x != 0 or player1CameraAngles.y != 0){
        this->m_cameraPlayer1.angles += player1CameraAngles;
        this->m_cameraPlayer1.camera.rotate(this->m_deltaTime, player1CameraAngles);
    }
    if(player2CameraAngles.x != 0 or player2CameraAngles.y != 0){
        this->m_cameraPlayer2.angles += player2CameraAngles;
        this->m_cameraPlayer2.camera.rotate(this->m_deltaTime, player2CameraAngles);
    }
    
    this->m_player1_object->setOrientation(this->m_cameraPlayer1.camera.getOrientation());
    this->m_player2_object->setOrientation(this->m_cameraPlayer2.camera.getOrientation());

}

void Renderer::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->renderPart(LEFT_PART);
    this->renderPart(RIGHT_PART);

    glViewport(0, 0, this->m_frameBufferWidth, this->m_frameBufferHeight);
    if(m_logic->isLaunched()){
        this->m_overlay.draw();
    }
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
    this->m_player1_object->draw(cameraToUse.camera.getViewMatrix(), cameraToUse.camera.getProjectionMatrix());
    this->m_player2_object->draw(cameraToUse.camera.getViewMatrix(), cameraToUse.camera.getProjectionMatrix());
    this->m_target->draw(cameraToUse.camera.getViewMatrix(), cameraToUse.camera.getProjectionMatrix());
	// TODO: render other game objects
}

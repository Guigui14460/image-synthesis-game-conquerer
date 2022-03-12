#ifndef __BACKGROUND_RENDERER_HPP__
#define __BACKGROUND_RENDERER_HPP__
#include "glApi.hpp"
#include <cmath>
#include <vector>
#include <glm/ext.hpp>
#include "Mesh.hpp"

struct GLFWwindow;

constexpr float PI = glm::pi<float>();
constexpr float MIN_ANGLE_BACKGROUND = 0.f;
constexpr float MAX_ANGLE_BACKGROUND = 2.f * PI;

class BackgroundRenderer
{
public:
    BackgroundRenderer(uint numberOfStars);
    BackgroundRenderer(const BackgroundRenderer& o) = delete;

    void initGLState() const;
    void createVAO(uint numberOfStars);
    void resize(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);
    void update();
    void continuousKey();
    void renderFrame();

private:
    std::vector<glm::vec3> generateRandomStars(uint numberOfStars);
    std::vector<float> generateRandomSizes(uint numberOfStars, float min, float max);


private:
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    std::shared_ptr<VAO> m_vao;
    Program m_program;
    glm::mat4 m_proj;
    glm::mat4 m_view;

    float m_eyePhi;
    float m_eyeTheta;

    float m_currentTime;
    float m_deltaTime;
};

#endif // __BACKGROUND_RENDERER_HPP__

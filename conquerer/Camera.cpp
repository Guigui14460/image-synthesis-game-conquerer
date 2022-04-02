#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
    : m_position(position), m_orientation(glm::normalize(direction)), m_worldUp(glm::normalize(worldUp)),
      m_up(glm::normalize(worldUp)), m_projectionMatrix(1.f), m_viewMatrix(1.f) {}

void Camera::move(const float &deltaTime) {
    this->m_position += deltaTime * this->m_orientation;
}

void Camera::rotate(const float &deltaTime, const glm::vec2 &rotation) {
    glm::vec2 rot = glm::radians(rotation) * deltaTime;

    // for pitch (phi for x-axis)
    glm::vec3 right = glm::normalize(glm::cross(this->m_up, this->m_orientation));
    this->m_orientation = glm::vec3(glm::normalize(glm::rotate(glm::mat4(1), rot.x, right) * glm::vec4(this->m_orientation, 0.f)));
    this->m_up = glm::normalize(glm::cross(this->m_orientation, right));

    // for yaw (theta for y-axis)
    glm::mat4 rotationMat = glm::rotate(glm::mat4(1), rot.y, this->m_worldUp);
    this->m_orientation = glm::vec3(glm::normalize(rotationMat * glm::vec4(this->m_orientation, 0.f)));
    this->m_up = glm::vec3(glm::normalize(rotationMat * glm::vec4(this->m_up, 0.f)));
}

glm::mat4 Camera::calculateProjectionMatrix(const float fov, const int frameBufferWidth, const int frameBufferHeight, const float nearPlane, const float farPlane) {
    this->m_projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);
    return this->m_projectionMatrix;
}

glm::mat4 Camera::calculateViewMatrix(){
    this->m_viewMatrix = glm::lookAt(this->m_position, this->m_position + this->m_orientation, this->m_up);
    return this->m_viewMatrix;
}

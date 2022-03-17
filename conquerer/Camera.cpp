#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
    : m_position(position), m_orientation(glm::normalize(direction)), m_worldUp(glm::normalize(worldUp)),
      m_projectionMatrix(1.f), m_viewMatrix(1.f), m_theta(0), m_phi(0.f) {}

void Camera::move(const float &deltaTime, const glm::vec3 &position) {
    this->m_position += position * deltaTime;
}

void Camera::rotate(const float &deltaTime, const glm::vec2 &rotation) {
    this->m_theta += deltaTime * rotation.y;
    this->m_phi += deltaTime * rotation.x;

    if(this->m_theta > 89.9)
        this->m_theta = 89.9;
    else if(this->m_theta < -89.9)
        this->m_theta = -89.9;

    if(this->m_phi > 360.f or this->m_phi < -360.f)
        this->m_phi = 0;

    glm::vec3 front;
    front.x = glm::cos(glm::radians(this->m_theta)) * glm::cos(glm::radians(this->m_phi));
    front.y = glm::sin(glm::radians(this->m_phi));
    front.z = glm::sin(glm::radians(this->m_theta)) * glm::cos(glm::radians(this->m_phi));

    this->m_orientation = glm::normalize(front);
}

glm::mat4 Camera::calculateProjectionMatrix(const float fov, const int frameBufferWidth, const int frameBufferHeight, const float nearPlane, const float farPlane) {
    this->m_projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);
    return this->m_projectionMatrix;
}

glm::mat4 Camera::calculateViewMatrix(){
//    glm::vec3 right = glm::normalize(glm::cross(this->m_orientation, this->m_worldUp));
//    glm::vec3 up = glm::normalize(glm::cross(right, this->m_orientation));

    this->m_viewMatrix = glm::lookAt(this->m_position, this->m_position + this->m_orientation, this->m_worldUp);
    return this->m_viewMatrix;
}

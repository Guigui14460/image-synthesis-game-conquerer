#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @brief The Camera class allows to see at some distance and some direction.
 */
class Camera {
public:
    Camera() = delete; /// Default constructor
    Camera(const Camera& o) = default; /// Copy constructor

    /**
     * @brief Camera constructor
     * @param position position of the camera in 3d euclidian space
     * @param direction direction of the camera in the space
     * @param worldUp the vector representing the up
     */
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);

    /// Gets the camera position
    inline glm::vec3 getPosition() const { return this->m_position; }
    /// Gets the camera direction
    inline glm::vec3 getOrientation() const  { return this->m_orientation; }

    /**
     * @brief Sets a new position for the camera object
     * @param position new camera position
     */
    inline void setPosition(const glm::vec3& position) { this->m_position = (position); }

    /**
     * @brief Sets a new direction for the camera object
     * @param orientation new direction
     */
    inline void setOrientation(const glm::vec3& orientation) { this->m_orientation = glm::normalize(orientation); }

    /// Gets the projection matrix
    inline glm::mat4 getProjectionMatrix() const { return this->m_projectionMatrix; }
    /// Gets the view matrix
    inline glm::mat4 getViewMatrix() const { return this->m_viewMatrix; }

    /**
     * @brief Moves the camera position
     * @param deltaTime elapsed time between last and current frame
     */
    void move(const float& deltaTime);

    /**
     * @brief Rotates the orientation of the camera object
     * @param deltaTime elapsed time between last and current frames
     * @param rotation 3d vector representing the rotation for the 3 axis
     */
    void rotate(const float& deltaTime, const glm::vec2& rotation);

    /**
     * @brief Updates the projection matrix.
     * @param fov field of vision in degrees (viewable proportion of the scene)
     * @param frameBufferWidth width of the current viewport
     * @param frameBufferHeight height of the current viewport
     * @param nearPlane the nearing retinal plane (min distance)
     * @param farPlane the far retinal plane (max distance)
     */
    glm::mat4 calculateProjectionMatrix(const float fov, const int frameBufferWidth, const int frameBufferHeight, const float nearPlane, const float farPlane);

    /// Updates the view matrix
    glm::mat4 calculateViewMatrix();

private:
    glm::vec3 m_position; /// Camera position in the space
    glm::vec3 m_orientation; /// Camera orientation in the space
    glm::vec3 m_worldUp; /// What is the direction of the up of the whole scene
    glm::vec3 m_up; /// Actual up of the camera
    glm::mat4 m_projectionMatrix; /// Projection matrix to make the perspective
    glm::mat4 m_viewMatrix; /// View matrix the see the object
};

#endif // __CAMERA_HPP__

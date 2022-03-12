#ifndef __MESH_HPP__
#define __MESH_HPP__
#include "glApi.hpp"

class Mesh
{
public:
    Mesh(std::shared_ptr<VAO> vao, glm::vec3 position = glm::vec3(0.f), glm::vec3 origin = glm::vec3(0.f),
         glm::vec3 rotate = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
    ~Mesh();
    Mesh(const Mesh& o) = delete;

    inline glm::vec3 getPosition() const { return this->m_position; }
    inline glm::vec3 getOrigin() const { return this->m_origin; }
    inline glm::vec3 getRotation() const { return this->m_rotation; }
    inline glm::vec3 getScale() const { return this->m_scale; }
    inline void setPosition(const glm::vec3& position) { this->m_position = position; }
    inline void setOrigin(const glm::vec3& origin) { this->m_origin = origin; }
    inline void setRotation(const glm::vec3& rotation) { this->m_rotation = rotation; }
    inline void setScale(const glm::vec3& scale) { this->m_scale = scale; }

    void updateProgram(Program& prog, const glm::mat4& projMatrix, const glm::mat4& viewMatrix = glm::mat4(1));
    void update(float deltaTime);
    void move(const glm::vec3& position);
    void rotate(const glm::vec3& rotation);
    void zoom(const glm::vec3& scale);
    void render(GLenum mode = GL_TRIANGLES);

private:
    void updateModelMatrix();

private:
    std::shared_ptr<VAO> m_vao;

    glm::vec3 m_position;
    glm::vec3 m_origin;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    glm::mat4 m_modelMatrix;
};

#endif // __MESH_HPP__

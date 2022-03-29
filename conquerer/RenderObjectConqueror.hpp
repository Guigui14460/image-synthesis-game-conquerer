#ifndef RENDEROBJECTCONQUEROR_HPP
#define RENDEROBJECTCONQUEROR_HPP
#include "Application.hpp"
#include "glApi.hpp"

class RenderObjectConqueror
{
public:
    RenderObjectConqueror(std::shared_ptr<VAO> vao, std::shared_ptr<Program> program, std::shared_ptr<Texture> texture);
    void draw(Sampler * colormap);
    void update(const glm::mat4 & mw);
    const std::shared_ptr<Texture> texture() const;
    const std::shared_ptr<Program> program() const;
    const std::shared_ptr<VAO> vao() const;

private:
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Program> m_program;
    std::shared_ptr<VAO> m_vao;
};

#endif // RENDEROBJECTCONQUEROR_HPP

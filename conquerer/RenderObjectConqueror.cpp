#include "RenderObjectConqueror.hpp"

RenderObjectConqueror::RenderObjectConqueror(std::shared_ptr<VAO> vao, std::shared_ptr<Program> program, const glm::vec3 & diffuse,std::shared_ptr<Texture> texture)
    : m_vao(vao), m_program(program), m_diffuse(diffuse), m_texture(texture)
{
}

void RenderObjectConqueror::draw(Sampler * colormap)
{
    m_program->bind();
    if (colormap) {
      colormap->attachTexture(*m_texture);
      colormap->attachToProgram(*m_program, "colorSampler", Sampler::DoNotBind);
    } else {
      const int unit = 0;
      glActiveTexture(GL_TEXTURE0 + unit);
      m_texture->bind();
      m_program->setUniform("colorSampler", unit);
    }
    m_vao->draw();
    m_program->unbind();
}

void RenderObjectConqueror::update(const glm::mat4 & mw)
{
    m_program->bind();
    m_program->setUniform("M", mw);
    m_program->unbind();
}

const std::shared_ptr<Texture> RenderObjectConqueror::texture() const{
    return m_texture;
}

const std::shared_ptr<Program> RenderObjectConqueror::program() const{
    return m_program;
}

const std::shared_ptr<VAO> RenderObjectConqueror::vao() const{
    return m_vao;
}

#include "RenderObjectConqueror.hpp"
#include "Image.hpp"
#include "SimpleMaterial.hpp"

//RenderObjectConqueror::RenderObjectConqueror(std::shared_ptr<VAO> vao, std::shared_ptr<Program> program,std::shared_ptr<Texture> texture)
//    : m_vao(vao), m_program(program),  m_texture(texture)
//{
//}

//void RenderObjectConqueror::draw(Sampler * colormap)
//{
//    m_program->bind();
//    if (colormap) {
//      colormap->attachTexture(*m_texture);
//      colormap->attachToProgram(*m_program, "colorSampler", Sampler::DoNotBind);
//    } else {
//      const int unit = 0;
//      glActiveTexture(GL_TEXTURE0 + unit);
//      m_texture->bind();
//      m_program->setUniform("colorSampler", unit);
//    }
//    m_vao->draw();
//    m_program->unbind();
//}

//void RenderObjectConqueror::update(const glm::mat4 & mw, const glm::mat4 & view, glm::mat4 & projection)
//{
//    m_program->bind();
//    m_program->setUniform("M", mw);
//    m_program->unbind();
//}

//const std::shared_ptr<Texture> RenderObjectConqueror::texture() const{
//    return m_texture;
//}

//const std::shared_ptr<Program> RenderObjectConqueror::program() const{
//    return m_program;
//}

//const std::shared_ptr<VAO> RenderObjectConqueror::vao() const{
//    return m_vao;
//}

#include "utils.hpp"
#include <ObjLoader.hpp>

RenderObject::RenderObject(const std::shared_ptr<Program> & program, const glm::mat4 & modelWorld) : m_program(program), m_mw(modelWorld)
{
  m_colormap = std::unique_ptr<Sampler>(new Sampler(0));
}

void RenderObject::draw()
{
  update();
  if (m_colormap) {
    m_colormap->bind();
  }
  for (auto & part : m_parts) {
    part.draw(m_colormap.get());
  }
  if (m_colormap) {
    m_colormap->unbind();
  }
}

std::shared_ptr<RenderObject> RenderObject::createWavefrontInstance(const std::shared_ptr<Program> & program, const std::string & objname, const glm::mat4 & modelWorld)
{
  std::shared_ptr<RenderObject> object(new RenderObject(program, modelWorld));
  object->loadWavefront(objname);
  return object;
}

void RenderObject::loadWavefront(const std::string & objname)
{
  ObjLoader objLoader(objname);
  const std::vector<SimpleMaterial> & materials = objLoader.materials();
  std::vector<glm::vec3> vextexPositions = objLoader.vertexPositions();
  const std::vector<glm::vec2> & vertexUVs = objLoader.vertexUVs();
  // set up the VBOs of the master VAO
  std::shared_ptr<VAO> vao(new VAO(2));
  vao->setVBO(0, vextexPositions);
  vao->setVBO(1, vertexUVs);
  size_t nbParts = objLoader.nbIBOs();
  for (size_t k = 0; k < nbParts; k++) {
    const std::vector<uint> & ibo = objLoader.ibo(k);
    if (ibo.size() == 0) {
      continue;
    }
    std::shared_ptr<VAO> vaoSlave;
    vaoSlave = vao->makeSlaveVAO();
    vaoSlave->setIBO(ibo);
    const SimpleMaterial & material = materials[k];
    Image<> colorMap = objLoader.image(material.diffuseTexName);
    std::shared_ptr<Texture> texture(new Texture(GL_TEXTURE_2D));
    texture->setData(colorMap);
    m_parts.push_back(RenderObjectPart(vaoSlave, m_program, texture));
  }
  m_colormap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  m_colormap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  m_colormap->setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  m_colormap->setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void RenderObject::update()
{
  for (auto & part : m_parts) {
    part.update(m_mw);
  }
}

RenderObjectPart::RenderObjectPart(std::shared_ptr<VAO> vao, std::shared_ptr<Program> program, std::shared_ptr<Texture> texture)
    : m_vao(vao), m_program(program), m_texture(texture)
{
}

void RenderObjectPart::draw(Sampler * colormap)
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

void RenderObjectPart::update(const glm::mat4 & mw)
{
  m_program->bind();
  m_program->setUniform("M", mw);
  m_program->unbind();
}

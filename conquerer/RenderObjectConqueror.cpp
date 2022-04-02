#include "RenderObjectConqueror.hpp"
#include "Image.hpp"
#include "SimpleMaterial.hpp"
#include "utils.hpp"
#include "ObjLoader.hpp"

RenderObject::RenderObject() : AbstractRenderObject(), m_colormap(new Sampler(0)) {}

void RenderObject::render(Program& prog, const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection, GLenum mode) {
  prog.bind();

  this->updateProgram(prog, view, projection);

  this->m_colormap->bind();
  for (auto & part : m_parts) {
    part.draw(m_colormap.get(), prog, model);
  }
  this->m_colormap->unbind();

  prog.unbind();
}

std::shared_ptr<RenderObject> RenderObject::createWavefrontInstance(const std::string & objname) {
  std::shared_ptr<RenderObject> object(new RenderObject());
  object->loadWavefront(objname);
  return object;
}

void RenderObject::loadWavefront(const std::string & objname) {
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
    m_parts.push_back(RenderObjectPart(vaoSlave, texture));
  }
  m_colormap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  m_colormap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  m_colormap->setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  m_colormap->setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void RenderObject::updateProgram(Program& prog, const glm::mat4 & view, const glm::mat4 & projection) {
    prog.setUniform("V", view);
    prog.setUniform("P", projection);
}

RenderObjectPart::RenderObjectPart(std::shared_ptr<VAO> vao, std::shared_ptr<Texture> texture)
    : m_vao(vao), m_texture(texture)
{
}

void RenderObjectPart::draw(Sampler * colormap, Program& prog, const glm::mat4 & model) {
    this->updateProgram(prog, model);
    colormap->attachTexture(*m_texture);
    colormap->attachToProgram(prog, "colorSampler", Sampler::DoNotBind);
    m_vao->draw();
}

void RenderObjectPart::updateProgram(Program& prog, const glm::mat4 & model) {
    prog.setUniform("M", model);
}

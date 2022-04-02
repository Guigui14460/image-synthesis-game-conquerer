#ifndef RENDEROBJECTCONQUEROR_HPP
#define RENDEROBJECTCONQUEROR_HPP

#include "glApi.hpp"
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class RenderObjectPart {
public:
  RenderObjectPart() = delete;
  RenderObjectPart(const RenderObjectPart &) = delete;
  RenderObjectPart(RenderObjectPart &&) = default;

  RenderObjectPart(std::shared_ptr<VAO> vao, std::shared_ptr<Program> program, std::shared_ptr<Texture> texture);
  void draw(Sampler * colormap);
  void update(const glm::mat4 & mw);

private:
  std::shared_ptr<VAO> m_vao;
  std::shared_ptr<Program> m_program;
  std::shared_ptr<Texture> m_texture;
};

class RenderObject {
public:
  RenderObject() = delete;
  RenderObject(const RenderObject &) = delete;

  static std::shared_ptr<RenderObject> createWavefrontInstance(const std::shared_ptr<Program> & program, const std::string & objname, const glm::mat4 & modelWorld);

  void draw();
  void update();

private:
  RenderObject(const std::shared_ptr<Program> & program, const glm::mat4 & modelWorld);
  void loadWavefront(const std::string & objname);
  static std::vector<GLubyte> makeCheckerBoard();

private:
  std::shared_ptr<Program> m_program;
  glm::mat4 m_mw; ///< modelWorld matrix
  std::vector<RenderObjectPart> m_parts;
  std::unique_ptr<Sampler> m_colormap;
};

#endif // RENDEROBJECTCONQUEROR_HPP

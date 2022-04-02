#ifndef __RENDER_OBJECT_CONQUEROR_HPP__
#define __RENDER_OBJECT_CONQUEROR_HPP__
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "glApi.hpp"
#include "AbstractRenderObject.hpp"

class RenderObjectPart {
public:
  RenderObjectPart() = delete;
  RenderObjectPart(const RenderObjectPart &) = delete;
  RenderObjectPart(RenderObjectPart &&) = default;

  RenderObjectPart(std::shared_ptr<VAO> vao, std::shared_ptr<Texture> texture);
  void draw(Sampler * colormap, Program& prog, const glm::mat4 & model);

private:
  void updateProgram(Program& prog, const glm::mat4 & model);

private:
  std::shared_ptr<VAO> m_vao;
  std::shared_ptr<Texture> m_texture;
};

class RenderObject: public AbstractRenderObject {
public:
  RenderObject();
  RenderObject(const RenderObject &) = delete;

  static std::shared_ptr<RenderObject> createWavefrontInstance(const std::string & objname);

  void render(Program& prog, const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES) override;

private:
  void loadWavefront(const std::string & objname);
  void updateProgram(Program& prog, const glm::mat4 & view, const glm::mat4 & projection);

private:
  std::vector<RenderObjectPart> m_parts;
  std::unique_ptr<Sampler> m_colormap;
};

#endif // __RENDER_OBJECT_CONQUEROR_HPP__

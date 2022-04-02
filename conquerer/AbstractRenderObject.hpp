#ifndef __ABSTRACT_RENDER_OBJECT_HPP__
#define __ABSTRACT_RENDER_OBJECT_HPP__
#include <glm/mat4x4.hpp>

#include "glApi.hpp"

class AbstractRenderObject {
public:
    AbstractRenderObject () {}

    virtual void render(Program& prog, const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_TRIANGLES) = 0;
};

#endif // __ABSTRACT_RENDER_OBJECT_HPP__

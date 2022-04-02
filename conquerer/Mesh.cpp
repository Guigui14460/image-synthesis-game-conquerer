#include "Mesh.hpp"

Mesh::Mesh(std::shared_ptr<VAO> vao) : AbstractRenderObject(), m_vao(vao) {}

void Mesh::updateProgram(Program& prog, const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection) {
    prog.setUniform("M", model);
    prog.setUniform("V", view);
    prog.setUniform("P", projection);
}

void Mesh::render(Program& prog, const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & projection, GLenum mode) {
    prog.bind();
    this->updateProgram(prog, model, view, projection);
    this->m_vao->draw(mode);
    prog.unbind();
}

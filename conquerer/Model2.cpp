#include "Model.hpp"

Model::Model(std::vector<std::shared_ptr<Mesh> > &meshes, std::shared_ptr<Texture> diffuseTexture)
    : m_meshes(meshes), m_diffuseTexture(diffuseTexture) {}

void Model::update(float /* deltaTime */) {}

void Model::render(Program &program, Sampler &sampler, const glm::mat4 &projViewMatrix, GLenum mode) {
    program.bind();

    sampler.attachTexture(*this->m_diffuseTexture.get());
    sampler.attachToProgram(program, "colorSampler", Sampler::DoNotBind);
    for(const auto& mesh: this->m_meshes){
        mesh->render(program, projViewMatrix, mode);
    }

    program.unbind();
}

std::shared_ptr<Mesh> Model::getMesh(unsigned int index) {
    if(index >= this->m_meshes.size()) throw "ERROR::MODEL::getMesh -> invalid index (out of bound)";

    return this->m_meshes[index];
}

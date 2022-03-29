#include "PlayerObject.hpp"
#include "ObjLoader.hpp"
#include "CollisionShapes.hpp"

PlayerObject::PlayerObject(player_t typePj, std::shared_ptr<Texture> texture,
                           std::shared_ptr<Mesh> mesh, glm::vec3 position,
                           std::shared_ptr<Program> program, const float health) : AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, health, glm::vec3(1)),
                    m_typePj(typePj), m_texture(texture), m_program(program){
    this->m_mesh = mesh;
}

std::shared_ptr<PlayerObject> PlayerObject::loadObjsPlayer(player_t typePj, glm::vec3 position, std::shared_ptr<Program> program, const float health)
{
    std::string texture = "";
    std::string object = "";

    if(typePj==PLAYER1){
        texture = "objConquerer/PJ/dolphin/Dolphin_texture.png";
        object = "objConquerer/PJ/dolphin/Dolphin.obj";
    }
    if(typePj==PLAYER2){
        texture ="objConquerer/PJ/shark/UV Shark.png";
        object = "objConquerer/PJ/shark/Shark.obj";
    }
    if(typePj==COMPUTER){
        texture ="objConquerer/computer/tuna/Tuna_texture.png";
        object = "objConquerer/computer/tuna/Tuna.obj";
    }

    std::shared_ptr<PlayerObject> objectnew = PlayerObject::loadObjs(typePj, object, texture, position, program, health);
    return objectnew;
}

std::shared_ptr<PlayerObject> PlayerObject::loadObjs(player_t typePj, const std::string & objname, const std::string & texturename, glm::vec3 position, std::shared_ptr<Program> program, const float health)
{
  std::shared_ptr<Texture> texture;
  ObjLoader objLoader(objname);
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
    texture = std::shared_ptr<Texture>(new Texture(GL_TEXTURE_2D));
    // TODO: texture->setData()
  }

  std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh(vao, position));

  PlayerObject objectnew (typePj,texture,mesh, position, program, health);

  return std::shared_ptr<PlayerObject> (&objectnew);
}

void PlayerObject::draw(const glm::mat4& projViewMatrix, GLenum mode){
    m_mesh->updateProgram(*m_program, projViewMatrix);

    // rendering
    m_program->bind();

    const int unit = 0;
    glActiveTexture(GL_TEXTURE0 + unit);
    m_texture->bind();
    m_program->setUniform("colorSampler", unit);

    m_mesh->render(mode);
    m_program->unbind();
}

void PlayerObject::update(){
}

PlayerObject::player_t PlayerObject::getPlayerType() {
    return this->m_typePj;
}

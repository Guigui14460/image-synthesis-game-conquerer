#include "PlayerObject.hpp"
#include "objectLoaderConqueror.hpp"
#include "CollisionShapes.hpp"
#include "utils.hpp"

#include <iostream>

PlayerObject::PlayerObject(player_t typePj, std::shared_ptr<Texture> texture,
                           std::shared_ptr<Mesh> mesh, glm::vec3 position,
                           std::shared_ptr<Program> program, std::vector<std::shared_ptr<RenderObjectConqueror>> parts,
                           std::shared_ptr<Sampler> colormap): AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, glm::vec3(1)),
                    m_typePj(typePj), m_texture(texture), m_mesh(mesh), m_program(program), m_parts(parts), m_colormap(colormap){}

std::shared_ptr<PlayerObject> PlayerObject::loadObjsPlayer(player_t typePj,  glm::vec3 position, std::shared_ptr<Program> program)
{
    std::string texture = "";
    std::string object = "";

    if(typePj==PLAYER1){
        texture = absolutename("objConquerer/PJ/dolphin/Dolphin_texture.png");
        object = absolutename("objConquerer/PJ/dolphin/Dolphin.obj");
//        object = absolutename("meshes/Tron/TronLightCycle.obj");
    }
    if(typePj==COMPUTER){
        texture = absolutename("objConquerer/PJ/shark/UV Shark.png");
        object = absolutename("objConquerer/PJ/shark/Shark.obj");
    }
    if(typePj==PLAYER2){
        texture = absolutename("objConquerer/asteroid/tuna/Tuna_texture.png");
        object = absolutename("objConquerer/asteroid/tuna/Tuna.obj");
    }

    return PlayerObject::loadObjs(typePj, object, texture, position, program);
}

std::shared_ptr<PlayerObject> PlayerObject::loadObjs(player_t typePj, const std::string & objname, const std::string & texturename, glm::vec3 position, std::shared_ptr<Program> program)
{
  std::vector<std::shared_ptr<RenderObjectConqueror>> parts;
  std::shared_ptr<Texture> texture;
  ObjectLoaderConqueror objLoader;
  objLoader.LoadFromFile(objname);
  objLoader.loadImage(texturename);

  std::vector<glm::vec3> vextexPositions = objLoader.vertexPosition();
//  std::vector<glm::vec3> vertexColors(vextexPositions.size());
//  for(size_t i = 0; i < vertexColors.size(); i++) {
//      vertexColors[i] = {1.f, 1.f, 1.f};
//  }
  const std::vector<glm::vec2> & vertexUVs = objLoader.vertexUV();

  // set up the VBOs of the master VAO
  std::shared_ptr<VAO> vao(new VAO(2));
  vao->setVBO(0, vextexPositions);
//  vao->setVBO(1, vertexColors);
  vao->setVBO(1, vertexUVs);

  size_t nbParts = objLoader.nbIBOs();
  for (size_t k = 0; k < nbParts; k++) {
    const std::vector<uint> & ibo = objLoader.ibos(k);
    if (ibo.size() == 0) {
      continue;
    }
    std::shared_ptr<VAO> vaoSlave;
    vaoSlave = vao->makeSlaveVAO();
    vaoSlave->setIBO(ibo);
    Image<> colorMap = objLoader.image(texturename);
    std::shared_ptr<Texture> texture(new Texture(GL_TEXTURE_2D));
    texture->setData(colorMap);
    RenderObjectConqueror* part = new RenderObjectConqueror(vaoSlave, program, texture);
    parts.push_back(std::shared_ptr<RenderObjectConqueror>(part));
  }

  std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh(vao, position));

//  program = std::make_shared<Program>("conquerer/3d.v.glsl", "conquerer/3d.f.glsl");

  std::shared_ptr<Sampler> colormap;

  //colormap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //colormap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //colormap->setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  //colormap->setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

  PlayerObject* objectnew = new PlayerObject(typePj,texture,mesh, position, program, parts, colormap);
  return std::shared_ptr<PlayerObject>(objectnew);
}

void PlayerObject::draw(){
    m_program->bind();
    update();
    if (m_colormap) {
      m_colormap->bind();
    }
    for (auto & part : m_parts) {
      part->draw(m_colormap.get());
    }
    if (m_colormap) {
      m_colormap->unbind();
    }
    m_program->unbind();
}

void PlayerObject::update(){
//    m_mesh->updateProgram(*m_program, glm::mat4(1), glm::mat4(1));
    m_program->setUniform("MVP", glm::mat4(1));
}

#include "PlayerObject.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include "CollisionShapes.hpp"
#include "utils.hpp"
//#include "objectLoaderConqueror.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

<<<<<<< HEAD
PlayerObject::PlayerObject(player_t typePj, std::shared_ptr<RenderObject> object, glm::vec3 position,
                           std::shared_ptr<Program> program, //std::vector<std::shared_ptr<RenderObjectConqueror>> parts,
                           std::shared_ptr<Sampler> colormap): AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, 0,glm::vec3(1)),
                    m_typePj(typePj), m_object(object), m_program(program), //m_parts(parts),
                    m_colormap(colormap){
                    }
=======
PlayerObject::PlayerObject(player_t typePj, std::shared_ptr<Texture> texture,
                           std::shared_ptr<Mesh> mesh, glm::vec3 position,
                           std::shared_ptr<Program> program, const float health) : AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, health, glm::vec3(1)),
                    m_typePj(typePj), m_texture(texture), m_program(program),
                    m_orientation(0) {
    this->m_mesh = mesh;
}
>>>>>>> origin/game_logic

std::shared_ptr<PlayerObject> PlayerObject::loadObjsPlayer(player_t typePj, glm::vec3 position, std::shared_ptr<Program> program, const float health)
{
    std::string texture = "";
    std::string object = "";

    if(typePj==COMPUTER){
        texture = absolutename("objConquerer/PJ/dolphin/Dolphin_texture.png");
        object = absolutename("objConquerer/PJ/dolphin/Dolphin.obj");

    }
    if(typePj==PLAYER2){
        texture = absolutename("objConquerer/PJ/shark/UV Shark.png");
        object = absolutename("objConquerer/PJ/shark/Shark.obj");
//        texture = absolutename("objConquerer/PJ/Tron/tire-spec.jpg");
//        object = absolutename("objConquerer/PJ/Tron/TronLightCycle.obj");
    }
    if(typePj==PLAYER1){
        texture = absolutename("objConquerer/asteroid/tuna/Tuna_texture.png");
        object = absolutename("objConquerer/asteroid/tuna/Tuna.obj");
    }

<<<<<<< HEAD
    return PlayerObject::loadObjs(typePj, object, texture, position, program);
=======
    std::shared_ptr<PlayerObject> objectnew = PlayerObject::loadObjs(typePj, object, texture, position, program, health);
    return objectnew;
>>>>>>> origin/game_logic
}

std::shared_ptr<PlayerObject> PlayerObject::loadObjs(player_t typePj, const std::string & objname, const std::string & texturename, glm::vec3 position, std::shared_ptr<Program> program, const float health)
{
/*    ObjLoader objLoader(objname);
    std::vector<std::shared_ptr<RenderObjectConqueror>> parts;
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
      vaoSlave = vao->makeSlaveVAO();//récupère les vbo et les met dans le slaveVAO
      vaoSlave->setIBO(ibo);
      const SimpleMaterial & material = materials[k];
      Image<> colorMap = objLoader.image(material.diffuseTexName);
 std::shared_ptr<Texture> texture(new Texture(GL_TEXTURE_2D));
      texture->setData(colorMap);
      RenderObjectConqueror* part = new RenderObjectConqueror(vaoSlave, program, material.diffuse, texture);
      parts.push_back(std::shared_ptr<RenderObjectConqueror>(part));
    }
    std::shared_ptr<Sampler> colorMap(new Sampler(0));

    colorMap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    colorMap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 std::shared_ptr<Texture> texture(new Texture(GL_TEXTURE_2D));


    std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh(vao, position));
    PlayerObject* objectnew = new PlayerObject(typePj,texture,mesh, position, program, parts, colorMap);
    return std::shared_ptr<PlayerObject>(objectnew);
**/
/*  std::vector<std::shared_ptr<RenderObjectConqueror>> parts;
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

<<<<<<< HEAD
//  program = std::make_shared<Program>("conquerer/3d.v.glsl", "conquerer/3d.f.glsl");
*/
  std::shared_ptr<Sampler> colormap = std::shared_ptr<Sampler>(new Sampler(0));
  colormap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  colormap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(3));
  glm::mat4 scale       = glm::scale(glm::mat4(1.f), glm::vec3(0.5));
  glm::mat4 rotation    = glm::rotate(glm::mat4(1.f), 1.f, {1.f, 0.f, 0.f});
  rotation    = glm::rotate(rotation, 1.f, {0.f, 1.f, 0.f});
  rotation    = glm::rotate(rotation, 1.f, {0.f, 0.f, 1.f});
  std::shared_ptr<RenderObject> obj = RenderObject::createWavefrontInstance(program, objname, translation * rotation * scale);

  PlayerObject* objectnew = new PlayerObject(typePj, obj, position, program, colormap);
  return std::shared_ptr<PlayerObject>(objectnew);
=======
  PlayerObject objectnew (typePj,texture,mesh, position, program, health);
>>>>>>> origin/game_logic

}

<<<<<<< HEAD
void PlayerObject::draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode){
    std::cout<<"poisson"<< std::endl;
=======
void PlayerObject::draw(const glm::mat4& projViewMatrix, GLenum mode){
    m_mesh->updateProgram(*m_program, projViewMatrix);

    // rendering
>>>>>>> origin/game_logic
    m_program->bind();
    update(view, projection);


<<<<<<< HEAD
    if (m_colormap) {
      m_colormap->bind();
    }
//    for (auto & part : m_parts) {
//      part->draw(m_colormap.get());
//    }
    m_object->draw();
    if (m_colormap) {
      m_colormap->unbind();
    }
    m_program->unbind();
}

void PlayerObject::update(const glm::mat4 & view, const glm::mat4 & projection){
//    m_mesh->updateProgram(*m_program, glm::mat4(1), glm::mat4(1));
//    glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(3));
//    glm::mat4 scale       = glm::scale(glm::mat4(1.f), glm::vec3(0.5));
//    glm::mat4 rotation    = glm::rotate(glm::mat4(1.f), 1.f, {1.f, 0.f, 0.f});
//    rotation    = glm::rotate(rotation, 1.f, {0.f, 1.f, 0.f});
//    rotation    = glm::rotate(rotation, 1.f, {0.f, 0.f, 1.f});
//    m_program->setUniform("M", translation * rotation * scale);

    m_program->setUniform("V", view);
    m_program->setUniform("P", projection);
}

void PlayerObject::update(float deltaTime){

=======
    m_mesh->render(mode);
    m_program->unbind();
}

void PlayerObject::update(float deltaTime){
    this->m_position += deltaTime * this->m_orientation;
>>>>>>> origin/game_logic
}

PlayerObject::player_t PlayerObject::getPlayerType() {
    return this->m_typePj;
}

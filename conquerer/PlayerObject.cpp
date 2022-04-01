#include "PlayerObject.hpp"
#include "OBJLoader.hpp"
#include "CollisionShapes.hpp"
#include "utils.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include <iostream>

PlayerObject::PlayerObject(player_t typePj, std::shared_ptr<Model> model, std::shared_ptr<Mesh> mesh, std::shared_ptr<VAO> vao,
                 std::shared_ptr<Program> program, std::shared_ptr<Sampler> colormap, glm::vec3 position) :
                  AbstractGameObject(position, 0, 0, CollisionShapes::RECTANGLE, glm::vec3(1)),
                  m_typePj(typePj), m_mesh(mesh), m_vao(vao), m_model(model), m_program(program), m_colormap(colormap) {}

std::shared_ptr<PlayerObject> PlayerObject::loadObjsPlayer(player_t typePj, std::shared_ptr<Program> program, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    std::string texture = "";
    std::string object = "";

    if(typePj == PLAYER1){
        texture = absolutename("objConquerer/PJ/dolphin/Dolphin_texture.png");
        object = absolutename("objConquerer/PJ/dolphin/Dolphin.obj");
    }
    if(typePj == PLAYER2){
        texture = absolutename("objConquerer/PJ/shark/UV Shark.png");
        object = absolutename("objConquerer/PJ/shark/Shark.obj");
    }
    if(typePj == COMPUTER){
        texture = absolutename("objConquerer/asteroid/tuna/Tuna_texture.png");
        object = absolutename("objConquerer/asteroid/tuna/Tuna.obj");
    }

    return PlayerObject::loadObjs(typePj, object, texture, program, position, rotation, scale);
}

std::shared_ptr<PlayerObject> PlayerObject::loadObjs(player_t typePj, const std::string & objname, const std::string & texturename, std::shared_ptr<Program> program, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    std::shared_ptr<VAO> vao = OBJLoader::loadOBJ(objname, false, false);
std::cout << "vao ok" << std::endl;

  std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh(vao, position, glm::vec3(0.f), rotation, scale));
  std::vector<std::shared_ptr<Mesh>> meshes;
  meshes.push_back(mesh);
  std::cout << "mesh ok" << std::endl;

  std::shared_ptr<Image<>> image = OBJLoader::loadImage(texturename);
  std::shared_ptr<Texture> texture = std::shared_ptr<Texture>(new Texture(GL_TEXTURE_2D));
  texture->setData(*image.get(), true);
  std::cout << "texture ok" << std::endl;

  std::shared_ptr<Model> model = std::shared_ptr<Model>(new Model(meshes, texture));
  std::cout << "model ok" << std::endl;

  std::shared_ptr<Sampler> colormap = std::shared_ptr<Sampler>(new Sampler(0));
  colormap->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  colormap->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  std::cout << "sampler ok" << std::endl;

  PlayerObject* objectnew = new PlayerObject(typePj, model, mesh, vao, program, colormap, position);
  return std::shared_ptr<PlayerObject>(objectnew);
}

void PlayerObject::draw(){
    m_program->bind();
    update();

//    this->m_colormap->bind();
// //    this->m_model->render(*m_program.get(), *m_colormap.get());
//    this->m_mesh->render(*this->m_program.get(), glm::lookAt(glm::vec3(0,0,-3),glm::vec3(0,1,0),glm::vec3(0,0,1)));
//    m_colormap->unbind();

    m_vao->draw();

    m_program->unbind();
}

void PlayerObject::update(){}

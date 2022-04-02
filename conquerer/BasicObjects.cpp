#include "BasicObjects.hpp"
#include <glm/ext.hpp>

std::shared_ptr<VAO> BasicObjects::makeParamSurf(DiscreteLinRange rgPhi, DiscreteLinRange rgTheta,
                            const std::function<glm::vec3(float, float)> & posFunc,
                            bool isCyclicInPhi, bool isCyclicInTheta, const glm::vec3& color)
{
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> colors;
  std::vector<uint> ibo;
  for (uint kPhi = 0; kPhi < rgPhi.nbVals; kPhi++) {
    for (uint kTheta = 0; kTheta < rgTheta.nbVals; kTheta++) {
      float phi = rgPhi.value(kPhi);
      float theta = rgTheta.value(kTheta);
      glm::vec3 position = posFunc(phi, theta);
      positions.push_back(position);
      colors.push_back(color);
      if ((kPhi == rgPhi.nbVals - 1 and not isCyclicInPhi) or (kTheta == rgTheta.nbVals - 1 and not isCyclicInTheta)) {
        continue;
      }
      auto index = [&](uint i, uint j) { return (i % rgPhi.nbVals) * rgTheta.nbVals + (j % rgTheta.nbVals); };
      uint patchIndices[] = {
          index(kPhi, kTheta),     index(kPhi, kTheta + 1), index(kPhi + 1, kTheta),     // first triangle
          index(kPhi + 1, kTheta), index(kPhi, kTheta + 1), index(kPhi + 1, kTheta + 1), // second triangle
      };
      ibo.insert(ibo.end(), patchIndices, patchIndices + 6);
    }
  }

  std::shared_ptr<VAO> vao = std::make_shared<VAO>(2);
  vao->setVBO(0, positions);
  vao->setVBO(1, colors);
  vao->setIBO(ibo);
  return vao;
}

std::shared_ptr<VAO> BasicObjects::makeSphere(uint nbPhi, uint nbTheta, const glm::vec3& color, const float radius){
    auto posFunc = [&radius](float phi, float theta) { return glm::vec3(radius * cos(phi) * sin(theta), radius * sin(phi) * sin(theta), radius * (1 - cos(theta))); };

    const float pi = glm::pi<float>();
    return BasicObjects::makeParamSurf(DiscreteLinRange(nbPhi, 0, 2 * pi), DiscreteLinRange(nbTheta, 0, pi), posFunc, true, false, color);
}

std::shared_ptr<VAO> BasicObjects::makeCube(const glm::vec3 color) {
    std::vector<glm::vec3> positions = {
        // back
        {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5},
        {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5},

        // front
        {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
        {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5},

        // left
        {-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5},
        {-0.5, 0.5, 0.5}, {-0.5, 0.5, -0.5},

        // right
        {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5},
        {0.5, 0.5, 0.5}, {0.5, 0.5, -0.5},

        // up
        {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5},
        {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5},

        // down
        {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
        {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5},
    };
    std::vector<glm::vec3> colors(24);
    for(int i = 0; i < 24; i++) {
        colors[i] = color;
    }
    std::vector<uint> ibo = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23,
    };

    std::shared_ptr<VAO> vao = std::make_shared<VAO>(2);
    vao->setVBO(0, positions);
    vao->setVBO(1, colors);
    vao->setIBO(ibo);
    return vao;
}

std::shared_ptr<VAO> BasicObjects::makeUniformSquare(const std::vector<glm::vec2> positions, const glm::vec3 color) {
    if(positions.size() != 4) throw "ERROR::BasicObjects::makeUniformSquare -> square need to have exactly 4 vertices";

    std::vector<glm::vec3> colors(4);
    for(int i = 0; i < 4; i++) {
        colors[i] = color;
    }
    std::vector<uint> ibo = {0, 1, 2, 0, 2, 3};

    std::shared_ptr<VAO> vao = std::make_shared<VAO>(2);
    vao->setVBO(0, positions);
    vao->setVBO(1, colors);
    vao->setIBO(ibo);
    return vao;
}

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

std::shared_ptr<VAO> BasicObjects::makeSphere(uint nbPhi, uint nbTheta, const glm::vec3& color){
    auto posFunc = [](float phi, float theta) { return glm::vec3(cos(phi) * sin(theta), sin(phi) * sin(theta), 1 - cos(theta)); };

    const float pi = glm::pi<float>();
    return BasicObjects::makeParamSurf(DiscreteLinRange(nbPhi, 0, 2 * pi), DiscreteLinRange(nbTheta, 0, pi), posFunc, true, false, color);
}

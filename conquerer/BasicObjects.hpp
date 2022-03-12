#ifndef __BASIC_OBJECTS_HPP__
#define __BASIC_OBJECTS_HPP__
#include "glApi.hpp"
#include <functional>

class BasicObjects
{
public:
    BasicObjects() = delete;
    BasicObjects(const BasicObjects& o) = delete;

    /// a simple struct for discrete linear range of the form {minVal, minVal+delta,...,minVal+length}
    struct DiscreteLinRange {
      uint nbVals;  ///< the number of values in the range
      float minVal; ///< the minimum value of the range
      float length; ///< the lengh (max -min) of the range

      /// Constructor
      DiscreteLinRange(uint nbVals, float minVal, float length) : nbVals(nbVals), minVal(minVal), length(length) {}

      /// Returns the k^{th} value of the range
      float value(uint k) { return minVal + k * length / (nbVals - 1); }
    };

    static std::shared_ptr<VAO> makeParamSurf(DiscreteLinRange rgPhi, DiscreteLinRange rgTheta,
                                              const std::function<glm::vec3(float, float)> & posFunc,
                                              bool isCyclicInPhi, bool isCyclicInTheta, const glm::vec3& color);

    static std::shared_ptr<VAO> makeSphere(uint nbPhi, uint nbTheta, const glm::vec3& color);
};

#endif // __BASIC_OBJECTS_HPP__

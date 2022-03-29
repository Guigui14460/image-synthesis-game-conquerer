#ifndef __BASIC_OBJECTS_HPP__
#define __BASIC_OBJECTS_HPP__
#include "glApi.hpp"
#include <functional>

/**
 * @brief The BasicObjects class representing a set of primitive objects that can be quickly create by hands or by an algorithm.
 */
class BasicObjects
{
public:
    BasicObjects() = delete; /// Default constructor
    BasicObjects(const BasicObjects& o) = delete; /// Copy constructor
    BasicObjects(BasicObjects &&o) = delete; /// Moving constructor

    /// A simple struct for discrete linear range of the form {minVal, minVal+delta,...,minVal+length}
    struct DiscreteLinRange {
      uint nbVals;  /// The number of values in the range
      float minVal; /// The minimum value of the range
      float length; /// The lengh (max - min) of the range

      /// Constructor
      DiscreteLinRange(uint nbVals, float minVal, float length) : nbVals(nbVals), minVal(minVal), length(length) {}

      /// Returns the k^{th} value of the range
      float value(uint k) { return minVal + k * length / (nbVals - 1); }
    };

    /**
     * @brief Makes a parametric surface.
     * @param rgPhi discrete linear range for phi angle
     * @param rgTheta discrete linear range for theta angle
     * @param posFunc function passed to retrieve position with phi and theta angles
     * @param isCyclicInPhi boolean if the surface is cyclic in phi
     * @param isCyclicInTheta boolean if the surface is cyclic in theta
     * @param color the color of the sphere
     * @return a VAO (position + color) for displaying the parametric surface
     */
    static std::shared_ptr<VAO> makeParamSurf(DiscreteLinRange rgPhi, DiscreteLinRange rgTheta,
                                              const std::function<glm::vec3(float, float)> & posFunc,
                                              bool isCyclicInPhi, bool isCyclicInTheta, const glm::vec3& color);

    /**
     * @brief Generates a sphere.
     * @param nbPhi number of phi angle to generate
     * @param nbTheta number of theta angle to generate
     * @param color the color of the sphere
     * @return a VAO (position + color) for displaying the sphere
     *
     * @note More you generate phi and theta angles, more your sphere will be rounded.
     */
    static std::shared_ptr<VAO> makeSphere(uint nbPhi, uint nbTheta, const glm::vec3& color);
};

#endif // __BASIC_OBJECTS_HPP__

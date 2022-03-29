#ifndef OBJECTLOADERCONQUEROR_HPP
#define OBJECTLOADERCONQUEROR_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ObjectLoaderConqueror
{
public:
    ObjectLoaderConqueror();

    /**
     * @brief Charge data in file 'filename'
     * @param fileName
     */
    void LoadFromFile(const std::string fileName);

    /**
     * @brief return the position get with LoadFromFile of the vertex
     * @return vertexPosition
     */
    const std::vector<glm::vec3> & vertexPosition() const;

    /**
     * @brief return the position of the texture get with LoadFromFile of the vertex
     * @return vertexUV
     */
    const std::vector<glm::vec2> & vertexUV() const;

    /**
     * @brief return the normal position get with LoadFromFile of the vertex
     * @return vertexNormal
     */
    const std::vector<glm::vec3> & vertexNormal() const;

    /**
     * @brief return the size of the ibo get with LoadFileFrom
     * @return size of ibo
     */
    size_t nbIBOs() const;

    /**
     * @brief return the ibo
     * @param k for the number that we want to return of the ibo
     * @return ibo
     */
    const std::vector<unsigned int> & ibos(unsigned int k) const;

private:
    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec2> vertexTexcoords;
    std::vector<glm::vec3> vertexNormals;
    std::vector<unsigned int> vertexPositionsIndices;
    std::vector<unsigned int> vertexTexcoordsIndices;
    std::vector<unsigned int> vertexNormalsIndices;
    typedef std::vector<unsigned int> IBO;
    std::vector<IBO> ibo;

    /**
     * @brief return the first letter of the text's line
     * @param Line
     * @param text
     * @return char
     */
    bool StartWith(std::string& Line, const char* text);
};

#endif // OBJECTLOADERCONQUEROR_HPP

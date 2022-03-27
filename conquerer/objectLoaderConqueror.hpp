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

    void LoadFromFile(const std::string fileName);
    const std::vector<glm::vec3> & vertexPosition() const;
    const std::vector<glm::vec2> & vertexUV() const;
    const std::vector<glm::vec3> & vertexNormal() const;
    size_t nbIBOs() const;
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
    bool StartWith(std::string& Line, const char* text);
};

#endif // OBJECTLOADERCONQUEROR_HPP

#include "objectLoaderConqueror.hpp"
#include <iostream>
#include <fstream>

ObjectLoaderConqueror::ObjectLoaderConqueror(){

}

bool ObjectLoaderConqueror::StartWith(std::string& line, const char* text){
    ssize_t textlen = strlen(text);
    if(line.size() < textlen){
        return false;
    }
    for(ssize_t i=0; i< textlen; i++){
        if(line[i] != text[i]){
            return false;
        }
    }
    return true;
}

void ObjectLoaderConqueror::LoadFromFile(const std::string fileName){
    std::ifstream file(fileName);
    if(!file){
        std::cout << "ERROR::OBJLOADER::Could not open file." << std::endl;
    }
    std::string line;
    std::stringstream ss;
    glm::vec3 tmpVec3;
    glm::vec2 tmpVec2;
    unsigned int tmpGLint;
    while(std::getline(file, line)){
        if(StartWith(line, "v")){
            ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;
            vertexPositions.push_back(tmpVec3);
            tmpVec3 = glm::vec3();
        }else if(StartWith(line, "vt")){
            ss >> tmpVec2.x >> tmpVec2.y;
            vertexTexcoords.push_back(tmpVec2);
            tmpVec2 = glm::vec2();
        }else if(StartWith(line, "vn")){
            ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;
            vertexNormals.push_back(tmpVec3);
            tmpVec3 = glm::vec3();
        }else if(StartWith(line, "f")) {
            int counter = 0;
            while (ss >> tmpGLint) {
                if (counter == 0){
                    vertexPositionsIndices.push_back(tmpGLint);
                    ibo.push_back(vertexPositionsIndices);
                }else if (counter == 1){
                    vertexTexcoordsIndices.push_back(tmpGLint);
                    ibo.push_back(vertexTexcoordsIndices);
                }else if (counter == 3){
                    vertexNormalsIndices.push_back(tmpGLint);
                    ibo.push_back(vertexNormalsIndices);
                }if (ss.peek() == '/') {
                    ++counter;
                    ss.ignore(1, '/');
                }else if (ss.peek() == ' ') {
                    counter = 0;
                    ss.ignore(1, ' ');
                }
            }
        }
    }
}

const std::vector<unsigned int> & ObjectLoaderConqueror::ibos(unsigned int k) const{
    return ibo[k];
}

size_t ObjectLoaderConqueror::nbIBOs() const{
    size_t size = ibo.size();
    return size;
}

const std::vector<glm::vec3> & ObjectLoaderConqueror::vertexPosition() const{
    return vertexPositions;
}

const std::vector<glm::vec2> & ObjectLoaderConqueror::vertexUV() const{
    return vertexTexcoords;
}

const std::vector<glm::vec3> & ObjectLoaderConqueror::vertexNormal() const{
    return vertexNormals;
}

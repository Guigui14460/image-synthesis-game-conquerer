#include "objectLoaderConqueror.hpp"
#include <iostream>
#include <fstream>
#include "utils.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    std::cout << fileExists(fileName) << std::endl;
    std::ifstream file(fileName);
    if(!file){
        std::cout << "ERROR::OBJLOADER -> Could not open file " << fileName << std::endl;
    }
    std::string line;
    std::string prefix;
    std::stringstream ss;
    glm::vec3 tmpVec3;
    glm::vec2 tmpVec2;
    int incre = 0;
    unsigned int tmpGLint;
    while(!getline(file, line).eof() && line.size()>=2){
//        std::cout << "blabal2 " << incre<< std::endl;
        incre ++;
//        std::cout << "blabal3 " << line<< std::endl;
        ss.clear();
        ss.str(line);
        ss >> prefix;
//        std::cout << "blabal4 " << line<< std::endl;
        if(prefix == "v"){
            ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;
            vertexPositions.push_back(tmpVec3);
            tmpVec3 = glm::vec3(0);
        }else if(prefix == "vt"){
            ss >> tmpVec2.x >> tmpVec2.y;
            vertexTexcoords.push_back(tmpVec2);
            tmpVec2 = glm::vec2(0);
        }else if(prefix == "vn"){
            ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;
            vertexNormals.push_back(tmpVec3);
            tmpVec3 = glm::vec3(0);
        }else if(prefix == "f"){
            int counter = 0;
            while (!ss.eof()){
//                std::cout << "while faces count[" << counter << "]" << std::endl;
                ss >> tmpGLint;
                if (counter == 0){
                    vertexPositionsIndices.push_back(tmpGLint);
                }else if (counter == 1){
                    vertexTexcoordsIndices.push_back(tmpGLint);
                }else if (counter == 2){
                    vertexNormalsIndices.push_back(tmpGLint);
                }if (ss.peek() == '/') {
                    ++counter;
                    ss.ignore(1, '/');
                }else if (ss.peek() == ' ') {
                    counter = 0;
                    ss.ignore(1, ' ');
                }
//                std::cout << "fin "<< std::endl;
            }
        }
//        std::cout << "blabal " << incre<< std::endl;
    }
    //std::cout << "pass\n" << vertexPositions.size() << std::endl;
    //std::cout << vertexNormals.size() << std::endl;
    //
    //std::cout << vertexTexcoords.size() << std::endl;

    ibo.push_back(vertexPositionsIndices);
    ibo.push_back(vertexTexcoordsIndices);
    ibo.push_back(vertexNormalsIndices);
}

const std::vector<unsigned int> & ObjectLoaderConqueror::ibos(unsigned int k) const{
    return ibo[k];
}

size_t ObjectLoaderConqueror::nbIBOs() const{
    size_t size = ibo.size();
    return size;
}

Image<> ObjectLoaderConqueror::image(const std::string & name) const
{
    unsigned char white[4] = {255, 255, 255, 255};
    static Image<> defaultImage(white, 1, 1, 4);
    auto searchRes = m_images.find(name);
    if (searchRes != m_images.end()) {
      return searchRes->second;
    }
    return defaultImage;
}

const std::vector<glm::vec3> & ObjectLoaderConqueror::vertexPosition() const{
    return vertexPositions;
}

void ObjectLoaderConqueror::loadImage(std::string texture_filename)
{
  std::string key = texture_filename;
  if (texture_filename.length() > 0) {
    // Only load the texture if it is not already loaded
    if (m_images.find(key) == m_images.end()) {
      if (!fileExists(texture_filename)) {
        std::cerr << "Unable to find file: " << texture_filename << std::endl;
        exit(1);
      }

      Image<> image;
      image.depth = 1;
      image.data = stbi_load(texture_filename.c_str(), &image.width, &image.height, &image.channels, STBI_default);
      if (!image.data) {
        std::cerr << "Unable to load texture: " << texture_filename << std::endl;
        exit(1);
      }
      m_images[key] = image;
    }
  }
}


const std::vector<glm::vec2> & ObjectLoaderConqueror::vertexUV() const{
    return vertexTexcoords;
}

const std::vector<glm::vec3> & ObjectLoaderConqueror::vertexNormal() const{
    return vertexNormals;
}

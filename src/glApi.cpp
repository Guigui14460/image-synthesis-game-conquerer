#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "glApi.hpp"
#include "utils.hpp"

Buffer::Buffer(GLenum target) : m_location(0), m_target(target), m_attributeSize(0)
{
  glGenBuffers(1, &this->m_location);
}

Buffer::~Buffer()
{
  glDeleteBuffers(1, &this->m_location);
}

void Buffer::bind() const
{
  glBindBuffer(this->m_target, this->m_location);
}

void Buffer::unbind() const
{
  glBindBuffer(this->m_target, 0);
}

uint Buffer::attributeCount() const
{
  return m_attributeCount;
}

GLenum Buffer::attributeType() const
{
  return m_attributeType;
}

uint Buffer::attributeSize() const
{
  return m_attributeSize;
}

VAO::VAO(uint nbVBO) : m_location(0), m_vbos(nbVBO), m_ibo(GL_ELEMENT_ARRAY_BUFFER)
{
  for (auto & vbo : m_vbos) {
    vbo = std::shared_ptr<Buffer>(new Buffer(GL_ARRAY_BUFFER));
  }
  assert(nbVBO <= 16); // You may want to replace 16 by the real hardware limitation
  glGenVertexArrays(1, &this->m_location);
}

VAO::~VAO()
{
  glDeleteVertexArrays(1, &this->m_location);
}

void VAO::bind() const
{
  glBindVertexArray(this->m_location);
}

void VAO::unbind() const
{
  glBindVertexArray(0);
}

void VAO::encapsulateVBO(unsigned int attributeIndex) const
{
  Buffer* vbo = this->m_vbos.at(attributeIndex).get();

  this->bind();
  vbo->bind();
  glEnableVertexAttribArray(attributeIndex);
  glVertexAttribPointer(attributeIndex, vbo->attributeSize(), vbo->attributeType(), GL_FALSE, 0, 0);
  this->unbind();
}

std::shared_ptr<VAO> VAO::makeSlaveVAO() const
{
  unsigned int nbVBO = m_vbos.size();
  std::shared_ptr<VAO> slave(new VAO(nbVBO));
  slave->m_vbos = m_vbos;
  slave->bind();
  for (unsigned int attributeIndex = 0; attributeIndex < nbVBO; attributeIndex++) {
    slave->encapsulateVBO(attributeIndex);
  }
  slave->unbind();
  return slave;
}

void VAO::draw(GLenum mode) const
{
  this->bind();
  glDrawElements(mode, this->m_ibo.attributeCount() * this->m_ibo.attributeSize(), this->m_ibo.attributeType(), 0);
  this->unbind();
}

Shader::Shader(GLenum type, const std::string & filename) : m_location(0)
{
  std::string file_content = fileContent(filename);
  GLint length = file_content.length();
  GLchar* source = (GLchar *)file_content.c_str();

  this->m_location = glCreateShader(type);
  glShaderSource(this->m_location, 1, (const GLchar**)&source, &length);
  glCompileShader(this->m_location);

  char infoLog[INFO_LOG_LENGTH];
  GLint success;
  glGetShaderiv(this->m_location, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(this->m_location, INFO_LOG_LENGTH, NULL, infoLog);
    std::cerr << "ERROR::SHADER::SHADER -> shader compilation error for: " << filename << std::endl;
    std::cerr << infoLog << std::endl;
    exit(EXIT_FAILURE);
  }
}

Shader::~Shader()
{
  glDeleteShader(this->m_location);
}

uint Shader::location() const
{
  return m_location;
}

Program::Program(const std::string & vname, const std::string & fname) : m_location(0), m_vshader(GL_VERTEX_SHADER, vname), m_fshader(GL_FRAGMENT_SHADER, fname)
{
  this->m_location = glCreateProgram();

  glAttachShader(this->m_location, this->m_vshader.location());
  glAttachShader(this->m_location, this->m_fshader.location());

  glLinkProgram(this->m_location);

  char infoLog[INFO_LOG_LENGTH];
  GLint success;
  glGetProgramiv(this->m_location, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(this->m_location, INFO_LOG_LENGTH, NULL, infoLog);
    std::cerr << "ERROR::PROGRAM::PROGRAM -> program linking error" << std::endl;
    std::cerr << infoLog << std::endl;
    exit(EXIT_FAILURE);
  }

  glDetachShader(this->m_location, this->m_vshader.location());
  glDetachShader(this->m_location, this->m_fshader.location());
}

Program::~Program()
{
  glDeleteProgram(this->m_location);
}

void Program::bind() const
{
  glUseProgram(this->m_location);
}

void Program::unbind() const
{
  glUseProgram(0);
}

bool Program::getUniformLocation(const std::string & name, int & location) const
{
  const char* c = name.c_str();
  location = glGetUniformLocation(this->m_location, (GLchar*) c);
  return location != -1;
}

template <> void Program::uniformDispatcher(int location, const int & val)
{
  glUniform1i(location, val);
}

template <> void Program::uniformDispatcher(int location, const uint & val)
{
  glUniform1ui(location, val);
}

template <> void Program::uniformDispatcher(int location, const float & val)
{
  glUniform1f(location, val);
}

template <> void Program::uniformDispatcher(int location, const glm::vec2 & val)
{
  glUniform2fv(location, 1, glm::value_ptr(val));
}

template <> void Program::uniformDispatcher(int location, const glm::vec3 & val)
{
  glUniform3fv(location, 1, glm::value_ptr(val));
}

template <> void Program::uniformDispatcher(int location, const glm::vec4 & val)
{
  glUniform4fv(location, 1, glm::value_ptr(val));
}

template <> void Program::uniformDispatcher(int location, const glm::mat2 & val)
{
  glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

template <> void Program::uniformDispatcher(int location, const glm::mat3 & val)
{
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

template <> void Program::uniformDispatcher(int location, const glm::mat4 & val)
{
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

bool Program::bound() const
{
  int currentProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
  return m_location == (GLuint)currentProgram;
}

Texture::Texture(GLenum target) : m_location(0), m_target(target)
{
  glGenTextures(1, &this->m_location);
}

Texture::~Texture()
{
  glDeleteTextures(1, &this->m_location);
}

void Texture::bind() const
{
  glBindTexture(this->m_target, this->m_location);
}

void Texture::unbind() const
{
  glBindTexture(this->m_target, 0);
}

template <> void Texture::setData<GLubyte>(const Image<GLubyte> & image, bool mipmaps) const
{
  GLint format;
  switch (image.channels) {
    case 1:
      format = GL_RED;
      break;
    case 2:
      format = GL_RG;
      break;
    case 3:
      format = GL_RGB;
      break;
    case 4:
      format = GL_RGBA;
      break;
    default:
      throw "ERROR::TEXTURE::setData -> number of channels not supported!";
      break;
  }

  this->bind();
  switch (this->m_target) {
    case GL_TEXTURE_2D:
      glTexImage2D(this->m_target, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
      break;
    case GL_TEXTURE_3D:
      glTexImage3D(this->m_target, 0, format, image.width, image.height, image.depth, 0, format, GL_UNSIGNED_BYTE, image.data);
      break;
    default:
      throw "ERROR::TEXTURE::setData -> target not supported yet!";
      break;
  }

  if(mipmaps){
    glTexParameteri(this->m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(this->m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(this->m_target);
    glGenerateTextureMipmap(this->m_target);
  }
  this->unbind();
}

Sampler::Sampler(int texUnit) : m_location(0), m_texUnit(texUnit)
{
  glGenSamplers(1, &this->m_location);
}

Sampler::~Sampler()
{
  glDeleteSamplers(1, &this->m_location);
}

void Sampler::bind() const
{
  glBindSampler(this->m_texUnit, this->m_location);
}

void Sampler::unbind() const
{
  glBindSampler(this->m_texUnit, 0);
}

void Sampler::attachToProgram(const Program & prog, const std::string & samplerName, BindOption bindOption) const
{
  if(bindOption == BindOption::BindUnbind){
    prog.bind();
  }

  prog.setUniform(samplerName, this->m_texUnit);

  if(bindOption == BindOption::BindUnbind){
    prog.unbind();
  }
}

void Sampler::attachTexture(const Texture & texture) const
{
  //this->bind();
  glActiveTexture(GL_TEXTURE0 + this->m_texUnit);
  texture.bind();
  //this->unbind();
}

template <> void Sampler::setParameter<int>(GLenum paramName, const int & value) const
{
  glSamplerParameteri(this->m_location, paramName, value);
}

template <> void Sampler::setParameter<float>(GLenum paramName, const float & value) const
{
  glSamplerParameterf(this->m_location, paramName, value);
}

void Sampler::enableAnisotropicFiltering() const
{
  GLfloat maxAniso = 2.f;
  this->setParameter(GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
}

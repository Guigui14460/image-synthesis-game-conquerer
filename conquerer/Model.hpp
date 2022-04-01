#ifndef MODEL_HEADER_H_
#define MODEL_HEADER_H_

#include <vector>

#include <glm/vec3.hpp>

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "OBJLoader.hpp"

class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void updateUniforms();

public:
	Model(glm::vec3 position, Material* material,
		Texture* textureDiffuse, Texture* textureSpecular,
		std::vector<Mesh*> meshes);
	Model(glm::vec3 position, Material* material,
		Texture* textureDiffuse, Texture* textureSpecular,
		const char* objFilename);
	~Model();
	static std::unique_ptr<Model> modelFromOBJ(glm::vec3 position, Material* material,
		Texture* textureDiffuse, Texture* textureSpecular, const char* objFilename,
		glm::vec3 meshPosition = glm::vec3(0.f), glm::vec3 meshRotation = glm::vec3(0.f), glm::vec3 meshScale = glm::vec3(1.f));

	void rotate(const glm::vec3 rotation);
	void update();
	void render(Shader* shader);
};

#endif // !MODEL_HEADER_H_

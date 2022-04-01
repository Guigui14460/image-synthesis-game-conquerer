/****#include "Model.hpp"

Model::Model(glm::vec3 position, Material* material,
	Texture* textureDiffuse, Texture* textureSpecular,
	std::vector<Mesh*> meshes) {
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = textureDiffuse;
	this->overrideTextureSpecular = textureSpecular;
	for (auto* i: meshes)
		this->meshes.push_back(new Mesh(*i));

	for (auto& i : this->meshes) {
		i->move(this->position);
		i->setOrigin(this->position);
	}
}

Model::Model(glm::vec3 position, Material* material,
	Texture* textureDiffuse, Texture* textureSpecular,
	const char* objFilename) {
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = textureDiffuse;
	this->overrideTextureSpecular = textureSpecular;

	std::vector<Vertex> mesh = loadOBJ(objFilename);
	meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0,
		glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));

	for (auto& i : this->meshes) {
		i->move(this->position);
		i->setOrigin(this->position);
	}

}

Model::~Model() {
	for (auto*& i : this->meshes)
		delete i;
}

std::unique_ptr<Model> Model::modelFromOBJ(glm::vec3 position, Material* material,
	Texture* textureDiffuse, Texture* textureSpecular, const char* objFilename,
	glm::vec3 meshPosition, glm::vec3 meshRotation, glm::vec3 meshScale) {
	std::vector<Mesh*> meshes;
	std::vector<Vertex> vertices = loadOBJ(objFilename);
	meshes.push_back(new Mesh(vertices.data(), vertices.size(), NULL, 0,
		meshPosition, glm::vec3(0.f), meshRotation, meshScale));
	return std::unique_ptr<Model>(new Model(position, material, textureDiffuse, textureSpecular, meshes));
}

void Model::updateUniforms() {

}

void Model::rotate(const glm::vec3 rotation) {
	for (auto& i : this->meshes)
		i->rotate(rotation);
}

void Model::update() {

}

void Model::render(Shader* shader) {
	// update uniforms
	this->updateUniforms();

	// materials, textures
	this->material->sendToShader(*shader);

	// use program
	shader->activate();

	for (auto& i : this->meshes) {
		// activate textures
		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);

		// draw
		i->render(shader);
	}

	shader->deactivate();
}
***/

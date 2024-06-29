#include "Model.h"

Model::Model() {
	modelMatrix = glm::mat4(1.0f);
}

Model::~Model() {

}

void Model::addMesh(Mesh* newMesh) {
	meshes.push_back(newMesh);
}

glm::mat4 Model::getModelMatrix() {
	return modelMatrix;
}

void Model::moveTo(float x, float y, float z) {
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
}
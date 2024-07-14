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

void Model::rotateBy(float degrees, glm::vec3 axisOfRotation) {
	modelMatrix = glm::rotate(modelMatrix, degrees * toRadians, axisOfRotation);
}

void Model::scaleBy(float scale) {
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
}

void Model::renderModel(Shader* shader) {
	GLuint modelLocation = shader->getShaderUniformLocation("model");
	if (!meshes.empty()) {
		for (size_t i = 0; i < meshes.size(); i++) {
			meshes[i]->renderMesh(modelLocation);
		}
	}
}
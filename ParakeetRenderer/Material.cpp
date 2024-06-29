#include "Material.h"

Material::Material() {
	//create shader
	shader = new Shader();
}

Material::~Material() {
	shader->deleteShader();
}

void Material::activateMaterial() {
	shader->useShader();
}

void Material::addShaderStep(const char* fileLocation, GLenum shaderType) {
	shader->addShader(fileLocation, shaderType);
}

void Material::prepareShader() {
	shader->compileShader();
}

void Material::addMesh(Mesh* mesh) {
	meshes.push_back(mesh);
}

void Material::renderMeshes(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
	activateMaterial();
	//set projection matrix
	glUniformMatrix4fv(shader->getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//set view matrix
	glUniformMatrix4fv(shader->getViewLocation(), 1, GL_FALSE, glm::value_ptr(viewMatrix));

	if (!meshes.empty()) {
		for (size_t i = 0; i < meshes.size(); i++) {
			meshes[i]->renderMesh(shader->getModelLocation());
		}
	}
}
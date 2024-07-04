#include "Material.h"

Material::Material() {
	//create shader
	shader = new Shader();
	shininess = 0.0f;
	specIntensity = 0.0f;
}

Material::~Material() {
	shader->deleteShader();
}

void Material::activateMaterial() {
	shader->useShader();
	diffuseTexture->useTexture(GL_TEXTURE0);

	//set material properties
	glUniform1f(shader->getShaderUniformLocation("material.shininess"), shininess);
	glUniform1f(shader->getShaderUniformLocation("material.specularIntensity"), specIntensity);
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

void Material::renderMeshes(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, std::vector<DirectionalLight*> dLights, glm::vec3 cameraPos) {
	activateMaterial();

	//set lights
	for (size_t i = 0; i < dLights.size(); i++) {
		dLights[i]->useLight(shader);
	}

	//set camera pos
	glUniform3f(shader->getShaderUniformLocation("eyePos"), cameraPos.x, cameraPos.y, cameraPos.z);

	//set projection matrix
	glUniformMatrix4fv(shader->getShaderUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//set view matrix
	glUniformMatrix4fv(shader->getShaderUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

	if (!meshes.empty()) {
		for (size_t i = 0; i < meshes.size(); i++) {
			meshes[i]->renderMesh(shader->getShaderUniformLocation("model"));
		}
	}
}

void Material::addDiffuseTexture(const char* diffuseTextureLocation) {
	Texture* newTexture = new Texture(diffuseTextureLocation);
	diffuseTexture = newTexture;

	diffuseTexture->loadTexture();
}

void Material::setMaterialProperties(GLfloat shine, GLfloat sIntensity){
	shininess = shine;
	specIntensity = sIntensity;
}

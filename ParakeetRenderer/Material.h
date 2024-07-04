#pragma once
#include "Shader.h"
#include "GL/glew.h"
#include "Mesh.h"
#include "Texture.h"
#include "DirectionalLight.h"

class Shader;
class Mesh;
class Texture;
class DirectionalLight;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Material();
	~Material();

	//setup functions
	void addShaderStep(const char* fileLoc, GLenum shaderType);
	void prepareShader();
	void addDiffuseTexture(const char* textureFileLocation);
	void setMaterialProperties(GLfloat shine, GLfloat sIntensity);

	//rendering functions
	void activateMaterial();
	void addMesh(Mesh* mesh);
	void renderMeshes(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, std::vector<DirectionalLight*> dLights, glm::vec3 cameraPos);

private:
	//material properties
	GLfloat shininess;
	GLfloat specIntensity;

	//shader
	Shader* shader;

	//texture
	Texture* diffuseTexture;

	//mesh list (for batching?)
	std::vector<Mesh*> meshes;
};


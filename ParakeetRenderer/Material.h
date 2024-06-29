#pragma once
#include "Shader.h"
#include "GL/glew.h"
#include "Mesh.h"

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

	//rendering functions
	void activateMaterial();
	void addMesh(Mesh* mesh);
	void renderMeshes(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

private:
	//material properties

	//shader
	Shader* shader;

	//texture

	//mesh list (for batching?)
	std::vector<Mesh*> meshes;
};


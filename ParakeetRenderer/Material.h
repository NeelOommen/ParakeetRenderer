#pragma once
#include "Shader.h"
#include "GL/glew.h"
#include "Mesh.h"

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
	void renderMeshes();

private:
	//material properties

	//shader
	Shader* shader;

	//texture

	//mesh list (for batching?)
	std::vector<Mesh*> meshes;
};


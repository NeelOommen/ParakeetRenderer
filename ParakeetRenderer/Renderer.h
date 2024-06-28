#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Material.h"
#include "Mesh.h"

class Renderer
{
public:
	Renderer();
	Renderer(GLint width, GLint height, std::string wName);
	~Renderer();
	void setup();

	bool shouldCloseProgram();

	//data modification
	Material* addNewMaterial();
	void prepareShaders();

	void createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int* indices, unsigned int indexCnt, Material* mat);

	//rendering functions
	void start();
	void update();

private:
	Window* window;

	//materials list
	std::vector<Material*> materials;

	//models
	std::vector<Mesh*> meshes;
};


#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer();
	Renderer(GLint width, GLint height, std::string wName,
		glm::vec3 cameraPosition, glm::vec3 cameraUp);
	~Renderer();
	void setup();

	bool shouldCloseProgram();

	//data modification
	Material* addNewMaterial();
	void prepareShaders();

	Model* createModel();
	void createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int* indices, unsigned int indexCnt, Material* mat, Model* model);

	//rendering functions
	void start();
	void update();

private:
	Window* window;

	//camera
	Camera* camera;

	//materials list
	std::vector<Material*> materials;

	//models
	std::vector<Model*> models;
	std::vector<Mesh*> meshes;

	//overall projectionMatrix
	glm::mat4 projectionMatrix;

	//rendering methods
	void renderByMaterial();
};


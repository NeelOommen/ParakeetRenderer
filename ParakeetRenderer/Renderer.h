#pragma once
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"

class Window;
class Material;
class Mesh;
class Model;
class Camera;
class Texture;
class DirectionalLight;

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

	GLFWwindow* getWin();

	//data modification
	Material* addNewMaterial();
	void prepareShaders();

	Model* createModel();
	void createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int vertexSize, unsigned int* indices, unsigned int indexCnt, Material* mat, Model* model);

	void createDirectionalLight(GLfloat r, GLfloat g, GLfloat b,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);

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

	//lights
	std::vector<DirectionalLight*> directionalLights;
	unsigned int directionalLightCount;

	//rendering methods
	void renderByMaterial();
};


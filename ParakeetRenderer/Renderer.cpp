#include "Renderer.h"

Renderer::Renderer() {
	window = new Window();
	camera = new Camera();
}

Renderer::Renderer(GLint width, GLint height, std::string wName, glm::vec3 cameraPosition, glm::vec3 cameraUp) {
	window = new Window(width, height, wName);
	camera = new Camera(cameraPosition, cameraUp);
}

Renderer::~Renderer() {

}

bool Renderer::shouldCloseProgram() {
	return window->shouldWindowClose();
}

void Renderer::setup() {
	printf("Initializing Window");
	window->initialize();

	//setup projection matrix
	projectionMatrix = glm::perspective(45.0f, (GLfloat)window->getBufferWidth() / (GLfloat)window->getBufferHeight(), 0.1f, 100.0f);
}

void Renderer::renderByMaterial() {
	glm::mat4 view = camera->getViewMatrix();
	if (!materials.empty()) {
		for (size_t i = 0; i < materials.size(); i++) {
			materials[i]->renderMeshes(projectionMatrix, view);
		}
	}
}

void Renderer::update() {
	glfwPollEvents();

	//clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderByMaterial();

	window->swapBuffers();
}

void Renderer::start() {
	printf("Compiling Shaders\n");
	prepareShaders();

	glViewport(0, 0, 800, 600);
}

Material* Renderer::addNewMaterial() {
	Material* newMaterial = new Material();

	materials.push_back(newMaterial);

	return newMaterial;
}

void Renderer::prepareShaders() {
	for (size_t i = 0; i < materials.size(); i++) {
		materials[i]->prepareShader();
	}
}

void Renderer::createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int vertexSize, unsigned int* indices, unsigned int indexCnt, Material* mat, Model* model) {
	Mesh* newMesh = new Mesh();

	//create the mesh
	newMesh->createMesh(vertices, vertexCnt, vertexSize, indices, indexCnt, model);

	//assign the mesh to the material
	mat->addMesh(newMesh);

	//store meshes
	meshes.push_back(newMesh);

	//attach to the relevant model
	model->addMesh(newMesh);
}

Model* Renderer::createModel() {
	Model* newModel = new Model();
	models.push_back(newModel);

	return newModel;
}

GLFWwindow* Renderer::getWin() {
	return window->getWindow();
}
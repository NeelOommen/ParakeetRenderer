#include "Renderer.h"

Renderer::Renderer() {
	window = new Window();
	camera = new Camera();

	directionalLightCount = 0;
}

Renderer::Renderer(GLint width, GLint height, std::string wName, glm::vec3 cameraPosition, glm::vec3 cameraUp) {
	window = new Window(width, height, wName);
	camera = new Camera(cameraPosition, cameraUp);

	directionalLightCount = 0;
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
	glViewport(0, 0, window->getBufferWidth(), window->getBufferHeight());

	glm::mat4 view = camera->getViewMatrix();

	if (!materials.empty()) {
		for (size_t i = 0; i < materials.size(); i++) {
			materials[i]->renderMeshes(projectionMatrix, view, directionalLights, camera->getCameraPosition());
		}
	}
}

void Renderer::shadowPass() {
	for (size_t i = 0; i < directionalLightCount; i++) {
		Shader* shader = directionalLights[i]->getShadowMapShader();
		shader->useShader();

		//set viewport
		glViewport(0, 0, directionalLights[i]->getShadowMap()->getWidth(), directionalLights[i]->getShadowMap()->getHeight());
		directionalLights[i]->getShadowMap()->write();
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 lTransform = directionalLights[i]->calculateLightTransform();
		glUniformMatrix4fv(shader->getShaderUniformLocation("lightTransform"), 1, GL_FALSE, glm::value_ptr(lTransform));

		//render models
		if (!models.empty()) {
			for (size_t i = 0; i < models.size(); i++) {
				models[i]->renderModel(shader);
			}
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void Renderer::update() {
	glfwPollEvents();

	//clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shadowPass();
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

DirectionalLight* Renderer::createDirectionalLight(GLfloat r, GLfloat g, GLfloat b, GLfloat aIntensity, GLfloat dIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLint shadowWidth, GLint shadowHeight){
	DirectionalLight* newDirectionalLight = new DirectionalLight(r, g, b, aIntensity, dIntensity, xDir, yDir, zDir, shadowWidth, shadowHeight);

	directionalLights.push_back(newDirectionalLight);
	directionalLightCount++;

	return newDirectionalLight;
}

Model* Renderer::createModel() {
	Model* newModel = new Model();
	models.push_back(newModel);

	return newModel;
}

GLFWwindow* Renderer::getWin() {
	return window->getWindow();
}
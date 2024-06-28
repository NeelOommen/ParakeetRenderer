#include "Renderer.h"

Renderer::Renderer() {
	window = new Window();
}

Renderer::Renderer(GLint width, GLint height, std::string wName) {
	window = new Window(width, height, wName);
}

Renderer::~Renderer() {

}

bool Renderer::shouldCloseProgram() {
	return window->shouldWindowClose();
}

void Renderer::setup() {
	printf("Initializing Window");
	window->initialize();
}

void Renderer::update() {
	//render meshes by materials
	if (!materials.empty()) {
		for (size_t i = 0; i < materials.size(); i++) {
			materials[i]->renderMeshes();
		}
	}

	//swap buffers
	window->swapBuffers();
}

void Renderer::start() {
	printf("Compiling Shaders\n");
	prepareShaders();
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

void Renderer::createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int* indices, unsigned int indexCnt, Material* mat) {
	Mesh* newMesh = new Mesh();

	//create the mesh
	newMesh->createMesh(vertices, vertexCnt, indices, indexCnt);

	//assign the mesh to the material
	mat->addMesh(newMesh);

	//store meshes
	meshes.push_back(newMesh);
}
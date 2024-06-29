#include <iostream>

#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat testMesh[] = {
	//		x		y		z		u		v		nX		nY		nZ	
			-1.0f,	-1.0f,	-0.6f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			0.0f,	-1.0f,	1.0f,	0.5f,	0.0f,	0.0f,	0.0f,	0.0f,
			1.0f,	-1.0f,	-0.6f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			0.0f,	1.0f,	0.0f,	0.5f,	1.0f,	0.0f,	0.0f,	0.0f 
};

unsigned int testIndices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
};

int main() {
	Renderer engine;
	engine.setup();

	//setup
	Material* mat = engine.addNewMaterial();
	//setup material shader
	mat->addShaderStep("Shaders/vertex.shader", GL_VERTEX_SHADER);
	mat->addShaderStep("Shaders/fragment.shader", GL_FRAGMENT_SHADER);

	//create mesh
	Model* pyramid = engine.createModel();
	engine.createMesh(testMesh, 4 * 8, testIndices, 4 * 3, mat, pyramid);
	pyramid->moveTo(0.0f, 0.0f, -5.0f);


	//start rendering
	engine.start();
	while (!engine.shouldCloseProgram()) {
		engine.update();
	}

	return 0;
}
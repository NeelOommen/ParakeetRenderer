#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

GLfloat testMesh[] = {
	//		x		y		z		u		v		nX		nY		nZ		r		g		b
			-1.0f,	-1.0f,	-0.6f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,
			0.0f,	-1.0f,	1.0f,	0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,
			1.0f,	-1.0f,	-0.6f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,
			0.0f,	1.0f,	0.0f,	0.5f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,   1.0f
};

/*testMesh[] = {
	//		x		y		z		r		g		b
			-1.0f,	-1.0f,	-0.6f,	1.0f,	0.0f,	0.0f,
			0.0f,	-1.0f,	1.0f,	0.0f,	1.0f,	0.0f,
			1.0f,	-1.0f,	-0.6f,	0.0f,	0.0f,	1.0f,
			0.0f,	1.0f,	0.0f,	1.0f,	0.0f,   1.0f
};*/

unsigned int testIndices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
};

int main() {
	Renderer engine;
	engine.setup();

	Material* mat = engine.addNewMaterial();
	mat->addShaderStep("Shaders/vertex.shader", GL_VERTEX_SHADER);
	mat->addShaderStep("Shaders/fragment.shader", GL_FRAGMENT_SHADER);

	Model* pyramid = engine.createModel();
	engine.createMesh(testMesh, 4 * 11, 11, testIndices, 4*3, mat, pyramid);
	pyramid->moveTo(0.0f, 0.0f, -10.0f);
	pyramid->rotateBy(15, glm::vec3(0.0, 1.0f, 0.0f));

	engine.start();
	while (!engine.shouldCloseProgram()) {
		
		engine.update();

	}

	return 0;
}
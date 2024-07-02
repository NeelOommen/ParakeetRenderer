#define STB_IMAGE_IMPLEMENTATION
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

GLfloat testCube[] = {
			1.0f,	1.0f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	//0
			1.0f,	1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,   //1
			1.0f,	1.0f,	-1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.0f,	0.0f,   //2

			-1.0f,	1.0f,	-1.0f,	1.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,   //3
			-1.0f,	1.0f,	-1.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f,   //4
			-1.0f,	1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,   //5

			-1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	//6
			-1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,   //7
			-1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,   //8

			-1.0f,	-1.0f,	-1.0f,	1.0f,	1.0f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,   //9
			-1.0f,	-1.0f,	-1.0f,	1.0f,	1.0f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	0.0f,   //10
			-1.0f,	-1.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.0f,	0.0f,   //11

			-1.0f,	-1.0f,	1.0f,	0.0f,	1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,   //12
			-1.0f,	-1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.0f,   //13
			-1.0f,	-1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	//14

			1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,   //15
			1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,   //16
			1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,   //17

			1.0f,	-1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,   //18
			1.0f,	-1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	0.0f,   //19
			1.0f,	-1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,   //20

			1.0f,	-1.0f,	-1.0f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,   //21
			1.0f,	-1.0f,	-1.0f,	1.0f,	0.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.0f,   //22
			1.0f,	-1.0f,	-1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,   //23
};

unsigned int testIndices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
};

unsigned int cubeIndices[] = {
	0,	15,	21,
	15,	21,	18,
	1,	4,	16,
	7,	4,	16,
	17,	20,	14,
	17,	14,	8,
	3,	6,	9,
	6,	9,	12,
	22,	10,	19,
	10,	19,	13,
	2,	5,	23,
	11,	5,	23
};

GLfloat floorMesh[] = {
	-1.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,
	-1.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,
	1.0f,	0.0f,	-1.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,
	1.0f,	0.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f
};

unsigned int floorIndices[] = {
	0,1,2,
	1,2,3
};

int main() {
	Renderer engine;
	engine.setup();

	Material* brickMat = engine.addNewMaterial();
	brickMat->addDiffuseTexture("Assets/Textures/brick_wall_001_diffuse_4k.jpg");
	brickMat->addShaderStep("Shaders/vertex.shader", GL_VERTEX_SHADER);
	brickMat->addShaderStep("Shaders/fragment.shader", GL_FRAGMENT_SHADER);

	Material* floorMat = engine.addNewMaterial();
	floorMat->addDiffuseTexture("Assets/Textures/dirt.png");
	floorMat->addShaderStep("Shaders/vertex.shader", GL_VERTEX_SHADER);
	floorMat->addShaderStep("Shaders/fragment.shader", GL_FRAGMENT_SHADER);

	Model* pyramid = engine.createModel();
	engine.createMesh(testCube, 24 * 11, 11, cubeIndices, 12 * 3, brickMat, pyramid);
	pyramid->moveTo(0.0f, 0.0f, -5.0f);

	Model* floor = engine.createModel();
	engine.createMesh(floorMesh, 4*11, 11, floorIndices, 2*3, floorMat, floor);
	floor->moveTo(0.0f, -2.0f, -5.0f);
	floor->scaleBy(10);
	
	int factor = 1;

	int cnt = 0;

	engine.start();
	while (!engine.shouldCloseProgram()) {

		if (cnt <= 800) {
			cnt++;
		}
		else {
			cnt = 0;
		}

		if (cnt % 400 == 0) {
			factor *= -1;
		}


		pyramid->moveTo(0.0f, factor * 0.001f, 0.0f);
		pyramid->rotateBy(0.1, glm::vec3(0.0, 1.0f, 0.0f));

		engine.update();

	}

	return 0;
}
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

GLfloat verts[] = {
	//		x		y		z		
			-1.0f,	-1.0f,	0.0f,
			1.0f,	-1.0f,	0.0f,
			0.0f,	1.0f,	0.0f
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

	Shader shader;
	shader.addShader("Shaders/vertex.shader", GL_VERTEX_SHADER);
	shader.addShader("Shaders/fragment.shader", GL_FRAGMENT_SHADER);
	shader.compileShader();

	Mesh mesh;
	mesh.createMesh(verts, 9, testIndices, 12, nullptr);

	GLFWwindow* w = engine.getWin();

	glViewport(0, 0, 800, 600);

	while (!engine.shouldCloseProgram()) {
		glfwPollEvents();

		//clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.useShader();

		mesh.renderMesh(1);

		engine.update();
	}

	return 0;
}
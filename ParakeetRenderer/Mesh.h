#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Model.h"

class Model;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int vertexSize, unsigned int* indices, unsigned int indexCnt, Model* belongToModel);
	void renderMesh(GLuint modelLocation);
	void clearMesh();

private:
	GLuint vao, vbo, ibo;
	GLsizei indexCount;

	//model that mesh is a part of
	Model* model;
};


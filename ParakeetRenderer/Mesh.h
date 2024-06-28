#pragma once
#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int* indices, unsigned int indexCnt);
	void renderMesh();
	void clearMesh();

private:
	GLuint vao, vbo, ibo;
	GLsizei indexCount;
};


#include "Mesh.h"

Mesh::Mesh() {
	vao = 0;
	vbo = 0;
	ibo = 0;
	indexCount = 0;
}

Mesh::~Mesh() {
	clearMesh();
}

void Mesh::createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int* indices, unsigned int indexCnt, Model* belongToModel) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertexCnt, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh(GLuint modelLocation) {
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

void Mesh::clearMesh() {
	if (vao != 0) {
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	if (ibo != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &ibo);
		ibo = 0;
	}

	if (vbo != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	indexCount = 0;
}
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

void Mesh::createMesh(GLfloat* vertices, unsigned int vertexCnt, unsigned int vertexSize, unsigned int* indices, unsigned int indexCnt, Model* belongToModel) {
	indexCount = indexCnt;
	model = belongToModel;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indexCnt, indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertexCnt, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * vertexSize, 0); //position
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11, (void*)(sizeof(vertices[0]) * 3)); //texcoord
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11, (void*)(sizeof(vertices[0]) * 5)); //normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * vertexSize, (void*)(sizeof(vertices[0]) * 8)); //vert colour
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh(GLuint modelLocation) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model->getModelMatrix()));

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
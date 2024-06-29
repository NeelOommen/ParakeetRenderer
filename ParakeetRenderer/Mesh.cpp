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
	indexCount = indexCnt;
	model = belongToModel;

	//create and bind vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//create and bind ibo
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//fill ibo with data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indexCnt, indices,GL_STATIC_DRAW);

	//create and bind vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vbo with data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertexCnt, vertices, GL_STATIC_DRAW);

	//vertex format
	//x y z (position)
	//i j (texture coordinate)
	//u v w (normal)

	//vertex attribs
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0); //position
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3)); // texture coordinate
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5)); // normal

	//enable vertex attribs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh(GLuint modelLocation) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model->getModelMatrix()));
	//bind vao
	glBindVertexArray(vao);

	//bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//draw
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	//unbind
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
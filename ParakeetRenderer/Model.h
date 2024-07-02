#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Mesh.h"
#include "CommonValues.h"

class Mesh;

class Model
{
public:
	Model();
	~Model();

	glm::mat4 getModelMatrix();

	void addMesh(Mesh* newMesh);

	void moveTo(float x, float y, float z);
	void rotateBy(float degrees, glm::vec3 axisOfRotation);
	void scaleBy(float scale);

private:
	std::vector<Mesh*> meshes;

	glm::mat4 modelMatrix;
};


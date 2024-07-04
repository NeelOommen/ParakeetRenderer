#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light
{
public:
	Light();

	Light(GLfloat r, GLfloat g, GLfloat b, GLfloat aIntentsity, GLfloat dIntensity);

	~Light();
protected:
	//light properties
	glm::vec3 lightColour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	//shadow
	//ShadowMap

	glm::mat4 lightProjection;
};


#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShadowMap.h"

class Light
{
public:
	Light();

	Light(GLfloat r, GLfloat g, GLfloat b, 
		GLfloat aIntentsity, GLfloat dIntensity,
		GLint shadowWidth, GLint shadowHeight
	);

	~Light();

	ShadowMap* getShadowMap();
protected:
	//light properties
	glm::vec3 lightColour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	//shadow
	//ShadowMap
	ShadowMap* shadowMap;

	glm::mat4 lightProjection;
};


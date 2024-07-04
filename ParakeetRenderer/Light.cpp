#include "Light.h"

Light::Light() {
	//white light
	lightColour = glm::vec3(1.0f, 1.0f, 1.0f);

	ambientIntensity = 1.0f;
	diffuseIntensity = 1.0f;
}

Light::Light(GLfloat r, GLfloat g, GLfloat b, GLfloat aIntentsity, GLfloat dIntensity){
	lightColour = glm::vec3(r, g, b);

	ambientIntensity = aIntentsity;
	diffuseIntensity = dIntensity;
}

Light::~Light() {
	lightColour = glm::vec3(1.0f, 1.0f, 1.0f);

	ambientIntensity = 1.0f;
	diffuseIntensity = 1.0f;
}
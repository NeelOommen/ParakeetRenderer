#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 _position, glm::vec3 _up);
	~Camera();

	void moveCameraBy(float x, float y, float z);

	glm::mat4 getViewMatrix();
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	
};


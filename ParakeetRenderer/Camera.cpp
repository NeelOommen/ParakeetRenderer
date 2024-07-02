#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	front = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::Camera(glm::vec3 _position, glm::vec3 _up) {
	position = _position;
	up = _up;

	front = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void Camera::moveCameraBy(float x, float y, float z) {
	position += glm::vec3(x,y,z);
}
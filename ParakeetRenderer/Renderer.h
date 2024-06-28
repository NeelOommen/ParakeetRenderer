#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"

class Renderer
{
public:
	Renderer();
	Renderer(GLint width, GLint height, std::string wName);
	~Renderer();

	bool shouldCloseProgram();

	void start();
	void update();

private:
	Window* window;
};


#pragma 

#include <string>
#include <stdio.h>
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window();
	Window(GLint width, GLint height, std::string wName);
	~Window();

	void initialize();
	bool shouldWindowClose();
	void swapBuffers();

	GLint getBufferWidth();
	GLint getBufferHeight();

	GLFWwindow* getWindow();
private:
	GLFWwindow* window;

	GLint m_width, m_height;
	GLint bufferWidth, bufferHeight;

	std::string windowName;


};


#include "Window.h"

Window::Window() {
	m_width = 800;
	m_height = 600;

	windowName = std::string("Test Window");

	//uninitialized
	bufferWidth = 0;
	bufferHeight = 0;
	window = nullptr;
}

Window::Window(GLint width, GLint height, std::string wName) {
	m_width = width;
	m_height = height;

	windowName = std::string(wName);

	//uninitialized
	bufferWidth = 0;
	bufferHeight = 0;
	window = nullptr;
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::initialize(){
	//load glfw
	if(!glfwInit()) {
		printf("Failed to initialize GLFW");
		glfwTerminate();
		return;
	}

	//set window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(m_width, m_height, windowName.c_str(), NULL, NULL);

	if (!window) {
		printf("Failed to create a window");
		glfwTerminate();
		return;
	}

	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW");
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

	if (!GLEW_VERSION_3_0) {
		printf("Failed 3.3 test");
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);
	printf("\nGL VERSION: %s\n", glGetString(GL_VERSION));
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

bool Window::shouldWindowClose() {
	return glfwWindowShouldClose(window);
}

GLint Window::getBufferWidth() {
	return bufferWidth;
}

GLint Window::getBufferHeight() {
	return bufferHeight;
}
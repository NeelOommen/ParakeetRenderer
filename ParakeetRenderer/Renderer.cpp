#include "Renderer.h"

Renderer::Renderer() {
	window = new Window();
}

Renderer::Renderer(GLint width, GLint height, std::string wName) {
	window = new Window(width, height, wName);
}

Renderer::~Renderer() {

}

bool Renderer::shouldCloseProgram() {
	return window->shouldWindowClose();
}

void Renderer::update() {
	window->swapBuffers();
}

void Renderer::start() {
	window->initialize();
}
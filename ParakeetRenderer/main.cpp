#include <iostream>

#include "Renderer.h"

int main() {
	Renderer engine;

	engine.start();

	while (!engine.shouldCloseProgram()) {
		engine.update();
	}

	return 0;
}
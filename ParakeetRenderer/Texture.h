#pragma once
#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:

	Texture();
	Texture(const char* fileLoc);
	~Texture();

	void loadTexture();

	void useTexture(GLenum textureUnit);
	void clearTexture();
private:
	//reference
	GLuint textureID;

	//texture data
	int width, height, depth;
	const char* textureFileLocation;

	//management
	bool nonEmptyFileLocation;
};


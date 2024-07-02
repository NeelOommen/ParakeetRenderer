#include "Texture.h"

Texture::Texture() {
	textureID = 0;

	width = 0;
	height = 0;
	depth = 0;

	textureFileLocation = (char*)"";

	nonEmptyFileLocation = false;
}

Texture::Texture(const char* fileLoc) {
	textureID = 0;

	width = 0;
	height = 0;
	depth = 0;

	textureFileLocation = fileLoc;
	nonEmptyFileLocation = true;
}

Texture::~Texture() {
	clearTexture();
}

void Texture::clearTexture() {
	if (textureID != 0) {
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}

	width = 0;
	height = 0;
	depth = 0;

	textureFileLocation = (char*)"";

	nonEmptyFileLocation = false;
}

void Texture::useTexture(GLenum textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::loadTexture() {
	if (!nonEmptyFileLocation) {
		printf("No file location to load a texture from\n");
		return;
	}

	//generate a new texture
	glGenTextures(1, &textureID);
	//bind the new texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	//set some default parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load image data
	unsigned char* texData = stbi_load(textureFileLocation, &width, &height, &depth, 0);

	if (!texData) {
		printf("STB failed to load image at %s", textureFileLocation);
		clearTexture();
		return;
	}

	GLenum imageType;
	if (depth == 4) {
		imageType = GL_RGBA;
	}
	else if(depth == 3) {
		imageType = GL_RGB;
	}
	else {
		printf("Texture Depth Error\n");
		clearTexture();
		return;
	}

	//move texture to gpu
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		imageType, 
		width, 
		height, 
		0,
		imageType, 
		GL_UNSIGNED_BYTE, 
		texData
	);
	//generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}


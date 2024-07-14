#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	fbo = 0;
	width = 0;
	height = 0;
	shadowMapID = 0;
}

ShadowMap::~ShadowMap()
{
	if (fbo) {
		glDeleteFramebuffers(1, &fbo);
	}

	if (shadowMapID) {
		glDeleteTextures(1, &fbo);
	}
}

GLuint ShadowMap::getWidth()
{
	return width;
}

GLuint ShadowMap::getHeight()
{
	return height;
}

bool ShadowMap::init(GLuint _width, GLuint _height)
{
	width = _width;
	height = _height;

	glGenFramebuffers(1, &fbo);

	glGenTextures(1, &shadowMapID);
	glBindTexture(GL_TEXTURE_2D, shadowMapID);
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_DEPTH_COMPONENT, 
		width, height, 
		0, 
		GL_DEPTH_COMPONENT, 
		GL_FLOAT, 
		nullptr
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float clampColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColour);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMapID, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//error checking
	GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer Error\n");
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void ShadowMap::write()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void ShadowMap::read(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, shadowMapID);
}

#pragma once
#include <stdio.h>
#include <GL/glew.h>

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	GLuint getWidth();
	GLuint getHeight();

	virtual bool init(GLuint _width, GLuint _height);
	virtual void write();
	virtual void read(GLenum textureUnit);
protected:
	//shadow data
	GLuint width, height;

	//gpu references
	GLuint fbo;
	GLuint shadowMapID;
};


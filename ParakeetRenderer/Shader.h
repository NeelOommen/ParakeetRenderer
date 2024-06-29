#pragma 
#include "GL/glew.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>

class Shader
{
public:
	Shader();
	~Shader();

	void addShader(const char* fileLocation, GLenum shaderType);
	void compileShader();

	void deleteShader();

	//rendering functions
	void useShader();
	GLuint getModelLocation();
	GLuint getViewLocation();
	GLuint getProjectionLocation();

private:
	GLuint shaderID;

	//uniforms
	GLuint modelLocation, viewLocation, projectionLocation;

	//shader creation stuff
	std::vector<std::pair<std::string, GLenum>> shaderCodeList;
	std::string readShaderFromFile(const char* fileLoc);
	void createShader(GLuint shader, const char* source, GLenum type);
	void getUniformLocations();

	//for management
	std::vector<GLuint> shaderIDList;
};


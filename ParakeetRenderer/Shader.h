#pragma 
#include "GL/glew.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>

class Shader
{
public:
	Shader();
	~Shader();

	void addShader(const char* fileLocation, GLenum shaderType);
	void compileShader();

	void deleteShader();

	void useShader();

private:
	GLuint shaderID;

	std::vector<std::pair<std::string, GLenum>> shaderCodeList;
	std::string readShaderFromFile(const char* fileLoc);
	void createShader(GLuint shader, const char* source, GLenum type);

	//for management
	std::vector<GLuint> shaderIDList;
};


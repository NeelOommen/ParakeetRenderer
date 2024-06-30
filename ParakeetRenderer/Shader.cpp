#include "Shader.h"

Shader::Shader() {
	shaderID = 0;
	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;
}

Shader::~Shader() {
	deleteShader();
}

std::string Shader::readShaderFromFile(const char* fileLoc) {
	std::string source;
	std::ifstream input(fileLoc, std::ios::in);

	if (!input.is_open()) {
		printf("Failed to open shader at %s", fileLoc);
		return "";
	}

	std::string line = "";
	while (!input.eof()) {
		std::getline(input, line);
		source.append(line + '\n');
	}

	//std::cout << source << "\n\n\n\n\n";

	return source;
}

void Shader::addShader(const char* fileLocation, GLenum shaderType) {
	std::string shaderSource = readShaderFromFile(fileLocation);

	if (shaderSource.length() <= 0) {
		printf("Failed to add shader");
		return;
	}

	shaderCodeList.push_back(std::make_pair(shaderSource, shaderType));
}

void Shader::createShader(GLuint program, const char* source, GLenum type) {
	GLuint shader = glCreateShader(type);

	//convert to glchar *
	const GLchar* code[1];
	code[0] = source;
	//get the length of the source
	GLint length[1];
	length[0] = strlen(source);

	//add the source
	glShaderSource(shader, 1, code, length);
	//compile
	glCompileShader(shader);

	//error check
	GLint result = 0;
	GLchar log[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		printf("%d Shader Compilation error: %s", type, log);
		return;
	}

	//attach to main program
	shaderIDList.push_back(shader);
	glAttachShader(program, shader);
}

void Shader::getUniformLocations() {
	//get the 3 main matrices
	modelLocation = glGetUniformLocation(shaderID, "model");
	viewLocation = glGetUniformLocation(shaderID, "view");
	projectionLocation = glGetUniformLocation(shaderID, "projection");

	printf("%d\n%d\n%d\n", modelLocation, viewLocation, projectionLocation);
}

void Shader::compileShader() {
	if (shaderCodeList.size() <= 0) {
		printf("No Shaders to compile");
		return;
	}
	printf("Compiling Shader...\n");
	shaderID = glCreateProgram();

	for (size_t i = 0; i < shaderCodeList.size(); i++) {
		const char* source = shaderCodeList[i].first.c_str();
		createShader(shaderID, source, shaderCodeList[i].second);
	}

	GLint result = 0;
	GLchar errorLog[1024] = { 0 };

	//link shader
	glLinkProgram(shaderID);

	//error check for linking
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		printf("Shader Compilation Error : %s", errorLog);
		return;
	}
	else {
		printf("Shader Linked\n");
	}

	//validate
	glValidateProgram(shaderID);

	//error check for validation
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		printf("Shader Compilation Error: %s", errorLog);
		return;
	}
	else {
		printf("Shader Validated\n");
	}

	//get all the uniform locations
	getUniformLocations();

	//printf("Compilation Successful\n");
}

void Shader::useShader() {
	glUseProgram(shaderID);
}

void Shader::deleteShader() {
	//delete individual shaders
	if (!shaderIDList.empty()) {
		for (size_t i = 0; i < shaderIDList.size(); i++) {
			glDeleteShader(shaderIDList[i]);
		}
		shaderIDList.clear();
		shaderCodeList.clear();
	}

	//delete the shader program
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;
}

//
//
//getter functions
//
//

GLuint Shader::getModelLocation() {
	return modelLocation;
}

GLuint Shader::getViewLocation() {
	return viewLocation;
}

GLuint Shader::getProjectionLocation() {
	return projectionLocation;
}
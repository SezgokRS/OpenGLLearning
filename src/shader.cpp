#include "../headers/shader.h"
#include <cstring>
#include <fstream>
#include <ios>
#include <string>

shader::shader(){
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

void shader::createFromString(const char* vertexCode, const char* fragmentCode){
    compileShader(vertexCode, fragmentCode);
}

std::string shader::readFile(const char* fileLocation){

    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    std::string line = "";

    while(!fileStream.eof()){
        std::getline(fileStream, line);
        content.append(line + '\n');
    }
    return content;
}

void shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation){
    std::string vertexString = readFile(vertexLocation);
    std::string fragmentString = readFile(fragmentLocation);

    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}

void shader::compileShader(const char* vertexCode, const char* fragmentCode){
    shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Failed to create shader\n");
		return;
	}

	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
	uniformModel = glGetUniformLocation(shaderID, "model");	uniformProjection = glGetUniformLocation(shaderID, "projection");
}

GLuint shader::getModelLocation(){
    return uniformModel;
}

GLuint shader::getProjectionLocation(){
    return uniformProjection;
}

void shader::useShader(){
    glUseProgram(shaderID);
}

void shader::clearShader(){
    if(shaderID != 0){
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}

void shader::addShader(GLuint theProgram, const char* shaderCode, GLuint shaderType){
    GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

shader::~shader(){
    clearShader();
}
#pragma once 
#ifndef _SHADER_H_
#define _SHADER_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class shader{
private:
    GLuint shaderID, uniformProjection, uniformModel;
    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLuint shaderType);

public:
    shader();
    void createFromFiles(const char* vertexLocation, const char* fragmentLocation);
    void createFromString(const char* vertexCode, const char* fragmentCode);

    std::string readFile(const char* fileLocation);

    GLuint getProjectionLocation();
    GLuint getModelLocation();
    void useShader();
    void clearShader();


    ~shader();
};



#endif
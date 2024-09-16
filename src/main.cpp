#include <glm/ext/matrix_transform.hpp>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h> 
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "../headers/mesh.h"
#include "../headers/shader.h"
#include "../headers/window.h"


// Window dimensions
const GLint WIDTH = 1920, HEIGHT = 1080;
const float RADIANS = 3.14159265f / 180.0f;
Window mainWindow;
GLuint shaderID, uniformModel, uniformProjection;

std::vector<mesh*> meshList;
std::vector<shader*> shaderList;
bool direction = true;
float triOffSet = 0.0f;
float triMaxOffSet = 0.7f;
float triIncrement = 0.0005f;
float curAngle = 0.0f;


// Vertex Shader code
static const char* vShader = "shaders/shader.vert";

// Fragment Shader
static const char* fShader = "shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[]{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,//0th indices
		0.0f, -1.0f, 1.0f,//1st indices
		1.0f, -1.0f, 0.0f,//2nd indices
		0.0f, 1.0f, 0.0f//3rd indices
	};

	mesh *obj1 = new mesh();
	obj1->createMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	mesh *obj2 = new mesh();
	obj2->createMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);

}

void CreateShaders(){
	shader* shader1 = new shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}


int main()
{
	mainWindow = Window(1920, 1080);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	GLuint uniformModel = 0, uniformProjection = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (direction) {
			triOffSet += triIncrement;
			if (abs(triOffSet) >= triMaxOffSet) {
				direction = false;
			}
		}
		else {
			triOffSet -= triIncrement;
			if (abs(triOffSet) >= triMaxOffSet) {
				direction = true;
			}

		}

		curAngle += 0.05f;
		if (curAngle >= 360.0f) {
			curAngle = 0.0f;
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//look up what this does
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->useShader();
		uniformModel = shaderList[0]->getModelLocation();
		uniformProjection = shaderList[0]->getProjectionLocation();

		//TRANSFORMATIONS (IMPORTANT)
		glm::mat4 model(1.0f);
		//order of these transformations are important since things move realtively to their origin and other things
		model = glm::translate(model, glm::vec3(0.0f, .0f, -2.0f));
		//model = glm::rotate(model, curAngle * RADIANS, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(.4f, .4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//model is not in the raw format so we need to point to it (??)
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->renderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-triOffSet, -triOffSet, -2.0f));
		//model = glm::rotate(model, curAngle * RADIANS, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(.4f, .4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//model is not in the raw format so we need to point to it (??)
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[1]->renderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
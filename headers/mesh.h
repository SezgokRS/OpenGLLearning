#pragma once
#ifndef _MESH_H_
#define _MESH_H_
#include <GL/glew.h>
class mesh{
public:
	mesh();
	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();
	~mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};
#endif

#include "../headers/mesh.h"

mesh::mesh(){
	VAO = 0;
  	VBO = 0;
  	IBO = 0;
  	indexCount = 0;
}

void mesh::createMesh(GLfloat *vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices){
  	indexCount = numOfIndices;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);// element array stores indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void mesh::renderMesh(){
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}

//deleting buffer off from graphics card
void mesh::clearMesh(){
	if (IBO != 0){
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	if (VBO != 0){
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0){
		__glewDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	indexCount = 0;
}

mesh::~mesh(){
	clearMesh();
}
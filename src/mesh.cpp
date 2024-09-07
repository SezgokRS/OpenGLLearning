#include "../headers/mesh.h"

Mesh::Mesh(){
  VAO = 0;
  VBO = 0;
  IBO = 0;
  indexCount = 0;
}

void Mesh::createMesh(GLfloat)

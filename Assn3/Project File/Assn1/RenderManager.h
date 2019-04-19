#pragma once
#include "State.h"
#include <map>


class RenderManager
{
public:
	bool enqueueMesh(UnitMesh mesh);
	RenderManager(State* state, GLFWwindow* &win);
	bool drawObject(UnitRequest reqinfo);
	void setVAO(GLuint ID) { VAO = ID; }
private:
	std::map<GLuint,UnitMesh> Meshqueue;//(ID,UnitMesh)
	State* StateRef;
	GLFWwindow* window; // (�ļ��Ǵ� �ڵ带 ����, �� ������ ����(Global)�Դϴ�.)
	GLuint VAO;
};
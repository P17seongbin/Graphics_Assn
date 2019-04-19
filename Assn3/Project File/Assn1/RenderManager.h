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
	GLFWwindow* window; // (후술되는 코드를 보면, 이 변수는 전역(Global)입니다.)
	GLuint VAO;
};
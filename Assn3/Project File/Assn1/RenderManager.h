#pragma once
#include "State.h"
#include <map>
#include <vector>


class RenderManager
{
public:
	bool enqueueMesh(UnitMesh mesh);
	RenderManager(State* state, GLFWwindow* &win);
	bool drawObject(std::vector<UnitRequest> &reqlist);
	void setVAO(GLuint ID) { VAO = ID; }
	glm::vec3 getCamPos();
private:
	std::map<GLuint,UnitMesh> Meshqueue;//(ID,UnitMesh)
	State* StateRef;
	GLFWwindow* window; // (후술되는 코드를 보면, 이 변수는 전역(Global)입니다.)
	GLuint VAO;
	glm::vec4 BGColor;
	glm::vec4 WireColor;


};
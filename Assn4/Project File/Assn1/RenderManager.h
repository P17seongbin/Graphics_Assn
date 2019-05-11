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
	glm::mat4 getLookAt();
private:
	std::map<GLuint,UnitMesh> Meshqueue;//(ID,UnitMesh)
	State* StateRef;
	GLFWwindow* window; // (�ļ��Ǵ� �ڵ带 ����, �� ������ ����(Global)�Դϴ�.)
	GLuint VAO;
	glm::vec4 BGColor;
	glm::vec4 WireColor;


};
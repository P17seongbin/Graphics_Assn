#pragma once
#include "State.h"
#include <map>

struct UnitRequest
{
	unsigned int PolygonID;
	glm::vec3 pos;
	glm::vec3 dir;
};

class RenderManager
{
public:
	bool enqueueMesh(GLuint ID, GLuint offset);
	RenderManager(State* state);
	bool drawObject(UnitRequest reqinfo);

private:
	std::map<GLuint, GLuint> Meshqueue;
	State* StateRef;
};
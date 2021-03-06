#pragma once
#include "IObject.h"
#include "RenderChannel.h"
class Ball : public IObject
{
public:
	Ball(RenderChannel * channel);
	glm::vec3 getPos() { return Pos; }
	glm::vec3 getSpeed() { return Speed; }
	glm::vec3 getAccel() { return Accel; }
	float getDir() { return Dir; }

	void setPos(glm::vec3 pos) { Pos = pos; }
	void setSpeed(glm::vec3 speed) { Speed = speed; }
	void setAccel(glm::vec3 accel) { Accel = accel; }
	void setDir(float dir) { Dir = dir; }
	void setBallPos(float ball_x) { Ball_x = ball_x; }
	//void setDir(glm::vec3 dir) { Dir = dir; }

	void addPos(glm::vec3 dpos) { Pos += dpos; }
	void addSpeed(glm::vec3 dspeed) { Speed += dspeed; }
	void addAccel(glm::vec3 daccel) { Accel += daccel; }
	void addDir(float ddir) { Dir += ddir; }
	//void addDir(glm::vec3 ddir) { Dir += ddir; }

	void setobjID(unsigned int i) { ID = i; }
	void setTag(std::string tag) { Tag = tag; }
	std::string getTag() { return Tag; }

	void DrawSelf() { Channel->EnqueueRequest(ID, Pos, Dir); }
	void Move(float dt);
	void update(GLFWwindow* window, float dt);
private:
	glm::vec3 Pos;
	glm::vec3 Speed;
	glm::vec3 Accel;
	float Dir;
	float Ball_x;//not used
	//glm::vec3 Dir;//보고있는 방향
	std::string Tag;
	unsigned int ID;
	RenderChannel* Channel;
};
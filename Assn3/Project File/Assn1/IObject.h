#pragma once

#include"State.h"
#include<string>

#define FIELD_WIDTH 50//코트 너비
#define FIELD_LENGTH 100 // 코트 길이(?)
/**
 * @brief: 오브젝트 인터페이스입니다. 각 Object는 아래와 같은 Method를 구현해야 합니다.
*/
class IObject
{
public:
	//IObject();
	virtual glm::vec3 getPos() = 0;
	virtual glm::vec3 getSpeed() = 0;
	virtual glm::vec3 getAccel() = 0;
	
	virtual void setPos(glm::vec3 pos) = 0;
	virtual void setSpeed(glm::vec3 speed) = 0;
	virtual void setAccel(glm::vec3 accel) = 0;

	virtual void addPos(glm::vec3 dpos) = 0;
	virtual void addSpeed(glm::vec3 dspeed) = 0;
	virtual void addAccel(glm::vec3 daccel) = 0;

	virtual void update(GLFWwindow* window) = 0;
	virtual void setobjID(unsigned int ID) = 0;

	virtual void setTag(std::string tag) = 0;
	virtual std::string getTag() = 0;

	virtual void setDir(float dir) = 0;
	virtual float getDir() = 0;
	virtual void addDir(float ddir) = 0;

	virtual void DrawSelf() = 0;

	virtual void Move(float dt) = 0;
};

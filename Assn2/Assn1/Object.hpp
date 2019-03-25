#include "KeyInputHandler.hpp"
#include "AABB.h"
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define SPEED 0.1
#pragma once

class Object
{
public:
	std::string tag;//이 오브젝트의 Tag를 나타냅니다.
	std::vector<AABB*> collidebox;//충돌 범위를 나타냅니다.
	Object()
	{

	}
	void Move(int dt)
	{
		float dx = (speed.first * dt) + (accel.first * dt * dt / (float)2);
		float dy = (speed.second * dt) + (accel.second * dt * dt / (float)2);
		addPos(dx, dy);
	}
	virtual void Draw()
	{
	}//이 오브젝트를 화면 상에 그리는 함수입니다.모든 오브젝트에 대해 구현해야만 합니다.
	virtual void Step(int dt)
	{
	}//매 프레임마다 할 행동을 나타냅니다. dt는 이전 프레임과 현재 프레임의 시간 차이를 나타냅니다.
	virtual void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB)
	{
	}//다른 Object와 충돌한 상황을 나타냅니다. 

	std::pair<float, float> getPos() { return pos; }
	void setPos(float x, float y) { pos = std::make_pair(x,y); }
	void addPos(float dx, float dy) { pos = std::make_pair(pos.first + dx, pos.second + dy); }
	
	const std::pair<float, float> getSpeed() { return speed; }
	void setSpeed(float vx, float vy) { speed = std::make_pair(vx,vy); }
	void addSpeed(float ax, float ay) { speed = std::make_pair(speed.first + ax, speed.second + ay);	}

	const std::pair<float, float> getAccel() { return accel; }
	void setAccel(float ax, float ay) { accel = std::make_pair(ax, ay);}

	void setSize(float x, float y) { size = std::make_pair(x, y); }
	std::pair<float, float> getSize() { return size; }
	
	void setRadius(float r) { radius = r; }
	float getRadius() { return radius; }

	void setParent(Object* p) { Parent = p; }
	Object* getParent() { return Parent; }
	
	bool isDestroy() { return destroyed; }
	void setDestroy(bool v) { destroyed = v; }

	std::pair<float, float>  getGlobalPos()
	{
		if (Parent == NULL)
			return pos;
		else
		{
			std::pair<float, float> t = Parent->getGlobalPos();
			return std::make_pair(pos.first + t.first, pos.second + t.second);
		}
	}
	void addChild(Object* c) { ChildList.push_back(c); }

protected:
		std::pair<float, float> pos;
		std::pair<float, float> size;
		std::pair<float, float> speed;
		std::pair<float, float> accel;
		float radius;
		bool destroyed = false;//이 오브젝트가 수명을 다했는지를 나타냅니다. 
		KeyHandler* keyhandler;
		std::vector<Object*> ChildList;//하위 캐릭터를 나타냅니다.
		Object* Parent;
};

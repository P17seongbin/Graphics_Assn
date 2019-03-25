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
	std::string tag;//�� ������Ʈ�� Tag�� ��Ÿ���ϴ�.
	std::vector<AABB*> collidebox;//�浹 ������ ��Ÿ���ϴ�.
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
	}//�� ������Ʈ�� ȭ�� �� �׸��� �Լ��Դϴ�.��� ������Ʈ�� ���� �����ؾ߸� �մϴ�.
	virtual void Step(int dt)
	{
	}//�� �����Ӹ��� �� �ൿ�� ��Ÿ���ϴ�. dt�� ���� �����Ӱ� ���� �������� �ð� ���̸� ��Ÿ���ϴ�.
	virtual void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB)
	{
	}//�ٸ� Object�� �浹�� ��Ȳ�� ��Ÿ���ϴ�. 

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
		bool destroyed = false;//�� ������Ʈ�� ������ ���ߴ����� ��Ÿ���ϴ�. 
		KeyHandler* keyhandler;
		std::vector<Object*> ChildList;//���� ĳ���͸� ��Ÿ���ϴ�.
		Object* Parent;
};

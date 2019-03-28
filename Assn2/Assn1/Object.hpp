#include "KeyInputHandler.hpp"
#include "AABB.h"
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define SPEED 0.1
#pragma once

typedef struct C3
{
	float r;
	float g;
	float b;
} Vector3;

class Object
{
public:
	std::string tag;//�� ������Ʈ�� Tag�� ��Ÿ���ϴ�.
	std::vector<AABB*> collidelist;//�浹 ������ ��Ÿ���ϴ�.
	Object()
	{
		anchor.first = pos.first;
		anchor.second = pos.second;
		angle = 0;
	}
	void Move(int dt)
	{
		float dx = (speed.first * dt) + (accel.first * dt * dt / (float)2);
		float dy = (speed.second * dt) + (accel.second * dt * dt / (float)2);
		addPos(dx, dy);
	}
	virtual void Draw()
	{
		glPushMatrix();
		glTranslatef(pos.first+anchor.first, pos.second+anchor.second, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-1 * anchor.first, -1 * anchor.second, 0);
		
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
	std::vector<Object*> getChildList(void){ return ChildList; }
	void setColor(float r, float g, float b) { color.r = r; color.b = b; color.g = g; }
	float getcolorR() { return color.r; }
	float getcolorG() { return color.g; }
	float getcolorB() { return color.b; }

	void setalpha(float w) { alpha = w; }
	float getalpha(void) { return alpha; }
	void setAnchor(float ax, float ay) { anchor.first = ax; anchor.second = ay; }

	void setAngle(float theta) { angle = theta; }
	float getAngle() { return angle; }

	std::pair<float, float> getAnchor() { return anchor; }

protected:
		std::pair<float, float> pos;
		std::pair<float, float> size;
		std::pair<float, float> speed;
		std::pair<float, float> accel;
		float radius;
		float alpha;
		bool destroyed = false;//�� ������Ʈ�� ������ ���ߴ����� ��Ÿ���ϴ�. 
		KeyHandler* keyhandler;
		std::vector<Object*> ChildList;//���� ĳ���͸� ��Ÿ���ϴ�.
		Object* Parent;
		Vector3 color;
		std::pair<float, float> anchor;//ȸ���� �������� ��Ÿ���ϴ�.
		float angle;//+x�� ���� CCW �������� �󸶳� ���ư������� ��Ÿ���ϴ�. ������ degree�Դϴ�.
};

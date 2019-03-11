#pragma once
#include "AABB.h"
#include<vector>
#include <GL/glew.h>
#include <GL/freeglut.h>

class Object
{
public:
	std::string tag;//�� ������Ʈ�� Tag�� ��Ÿ���ϴ�.
	std::vector<AABB*> collidebox;//�浹 ������ ��Ÿ���ϴ�.
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

	bool isDestroy() { return destroyed; }
	void setDestroy(bool v) { destroyed = v; }
protected:
		std::pair<float, float> pos;
		std::pair<float, float> speed;
		std::pair<float, float> accel;
		bool destroyed = false;//�� ������Ʈ�� ������ ���ߴ����� ��Ÿ���ϴ�. 
};

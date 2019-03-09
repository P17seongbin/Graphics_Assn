#pragma once
#include "AABB.h"
class Object
{
public:
	AABB* collidebox;//�浹 ������ ��Ÿ���ϴ�.
	
	Object();
	~Object();
	virtual void Draw() = 0;//�� ������Ʈ�� ȭ�� �� �׸��� �Լ��Դϴ�.��� ������Ʈ�� ���� �����ؾ߸� �մϴ�.
	virtual void Step(float dt) = 0;//�� �����Ӹ��� �� �ൿ�� ��Ÿ���ϴ�. dt�� ���� �����Ӱ� ���� �������� �ð� ���̸� ��Ÿ���ϴ�.
	virtual void onCollide(Object* other) = 0;//�ٸ� Object�� �浹�� ��Ȳ�� ��Ÿ���ϴ�. 

	const std::pair<float, float> getPos() { return pos; }
	void setPos(float x, float y) { pos.first = x; pos.second = y; }
	void addPos(float dx, float dy) { pos.first += dx; pos.second += dy; }

	const std::pair<float, float> getSpeed() { return speed; }
	void setSpeed(float vx, float vy) { pos.first = vx; pos.second = vy; }
	void addSpeed(float ax, float ay) { pos.first += ax; pos.second += ay; }

	const std::pair<float, float> getAccel() { return accel; }
	void setAccel(float ax, float ay) { pos.first = ax; pos.second = ay; }

private:
		std::pair<float, float> pos;
		std::pair<float, float> speed;
		std::pair<float, float> accel;
};


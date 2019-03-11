#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player()
	{
		tag = "Player";
		setSize(30, 10);
		setSpeed(3, 0);
	}
	void Step(int dt) override
	{
	}
	void Draw() override;
	void setSize(float x, float y) { size = std::make_pair(x, y); }
	std::pair<float, float> getSize() { return size; }

private:
	void Move(int dt);
	std::pair<float, float> size;
};

class Ball : public Object
{
public:
	Ball()
	{
		tag = "Ball";
		setRadius(1.0);
		setSpeed(0.2, 0.3);
	}
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override//지금은 충돌 안함
	{

	}
	void setRadius(float r) { radius = r; }
	float getRadius() { return radius; }

	void Step(int dt) override;
	void Draw() override;
private:
	float radius;
};
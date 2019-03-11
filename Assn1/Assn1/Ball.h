#pragma once
#include "Object.h"

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
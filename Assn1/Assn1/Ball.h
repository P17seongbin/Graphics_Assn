#pragma once
#include "Object.h"

class Ball : public Object
{
public:
	Ball()
	{
		tag = "Ball";
		setRadius(1.0);
		setSpeed(0.2, 0.15);
		AABB ball;
		ball.setType(0);
		ball.setPos(0, 0);
		collidebox.push_back(&ball);
	}
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override//지금은 충돌 안함
	{
		//printf("1");
		//setSpeed((-1)*speed.first,(-1)* speed.second);
	}
	void setRadius(float r) { radius = r; }
	float getRadius() { return radius; }

	void Step(int dt) override;
	void Draw() override;

	void updateAABB()
	{
		//collidebox[0]->setPos(getPos().first, getPos().second);
	}
	
private:
	float radius;
	
};
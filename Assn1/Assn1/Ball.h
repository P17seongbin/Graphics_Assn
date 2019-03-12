#pragma once
#include "Object.h"

class Ball : public Object
{
public:
	Ball();
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override//지금은 충돌 안함
	{
		if (otherAABB->getType() == 1)
		{
			if (pos.second > 30)
			{
				if (speed.second < 0)
					setSpeed(speed.first, -speed.second);
			}
			if (pos.first <= other->getPos().first)
			{
				if (speed.first > 0)
					setSpeed(-speed.first, speed.second);
			}
			if (pos.first >= other->getPos().first + 15)
			{
				if (speed.first < 0)
					setSpeed(-speed.first, speed.second);
			}
		}
		else//circle to circle
		{
			printf("1");
			setSpeed(-speed.first, -speed.second);
		}
	
	}
	void setRadius(float r) { radius = r; }
	float getRadius() { return radius; }

	void Step(int dt) override;
	void Draw() override;

	void updateAABB()
	{
		collidebox[0]->setPos(pos.first, pos.second);
	}
	
private:
	float radius;
	
};
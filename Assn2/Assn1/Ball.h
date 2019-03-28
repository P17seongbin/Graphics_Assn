#pragma once
#include "Object.hpp"
#define RADIUS 5.0

class Ball : public Object
{
public:
	Ball();
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override;
	void Step(int dt) override;
	void Draw() override;
	void Draw_Electricity();
	void updateAABB()
	{
		collidelist[0]->setPos(pos.first, pos.second);
	}
	bool IsCollidedwithP1 = false;
private:

};
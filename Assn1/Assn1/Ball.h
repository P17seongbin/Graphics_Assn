#pragma once
#include "Object.h"
#define RADIUS 2.0f
class Ball : public Object
{
public:
	Ball();
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override;
	void Step(int dt) override;
	void Draw() override;

	void updateAABB()
	{
		collidebox[0]->setPos(pos.first, pos.second);
	}
private:

};
#pragma once
#include "Object.h"
#define PI 3.14151

class Player : public Object
{
public:
	//BAAAAAAAAAAAD code!
	Player(KeyHandler* handler,bool _1P);
	void Step(int dt) override;
	void Draw() override;
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override;
	void updateAABB()
	{
		collidebox[1]->setPos(center_x, center_y);
		collidebox[0]->setPos(pos.first, pos.second);
	}
	void setminMax(float m, float M) { min = m; max = M; }
	void setMin(float val) { min = val; }
	
private:
	//std::pair<float, float> size;
	float head_rad;
	float body;
	float center_x;
	float center_y;
	float min;
	float max;
	bool is_1P;
};

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
	void setSize(float x, float y) { size = std::make_pair(x, y); }
	std::pair<float, float> getSize() { return size; }
	void updateAABB()
	{
		collidebox[0]->setPos(getPos().first, getPos().second);
	}
	
private:
	std::pair<float, float> size;
	float head_rad;
	float body;
	bool is_1P;
};

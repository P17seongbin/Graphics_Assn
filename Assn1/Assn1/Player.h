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
		
		center_x = pos.first + size.second / 2;
		center_y = size.first - head_rad;
		collidebox[1]->setPos(center_x, center_y);
		collidebox[0]->setPos(pos.first, pos.second);
	}
	
private:
	std::pair<float, float> size;
	float head_rad;
	float body;
	float center_x;
	float center_y;
	bool is_1P;
};

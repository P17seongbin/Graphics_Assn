#pragma once
#include "Object.hpp"
#include "Player.h"
#include "Assn2.h"

class Cloud : public Object
{
public:
	Cloud(float x, float y,float speed_x);

	void Draw(void) override;
	void Step(int dt) override;
private:
	float move_x;
	float move_y;
	float wing_speed;
	
};
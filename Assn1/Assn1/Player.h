#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player()
	{
		tag = "Player";
		setSize(30, 10);
		setSpeed(0, 0);
	}
	void Step(int dt) override
	{
		Move(dt);
	}
	void Draw() override;
	void setSize(float x, float y) { size = std::make_pair(x, y); }
	std::pair<float, float> getSize() { return size; }

private:
	std::pair<float, float> size;
};

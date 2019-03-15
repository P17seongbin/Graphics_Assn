#pragma once
#include "Object.h"

class Net : public Object
{
public:
	Net(float x, float y, float height, float width);
	void Step(int dt) override {}
	void Draw() override;
};

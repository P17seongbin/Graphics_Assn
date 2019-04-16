#pragma once
#include "Object.hpp"

class UnitRect : public Object
{
public:
	UnitRect(float x, float y, float height, float width);
	void Step(int dt) override {}
	void Draw() override;
};

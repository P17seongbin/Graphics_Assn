#include "AABB.h"
RectAABB::RectAABB()
{
	type = AABBType::Rect;
	SetCollider();
}
RectAABB::RectAABB(float x, float y, float first, float second) 
{ 
	size.first = first;
	size.second = second; 
	setPos(x, y); 
	type = AABBType::Rect;
	SetCollider();
}
CircleAABB::CircleAABB()
{
	type = AABBType::Circle;
	SetCollider();
}

CircleAABB::CircleAABB(float rad, float x, float y) {
	r = rad;
	setPos(x, y);
	type = AABBType::Circle;
	SetCollider();
}
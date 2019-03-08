#include "AABB.h"
RectAABB::RectAABB()
{
	type = AABBType::Rect;
	SetCollider();
}

CircleAABB::CircleAABB()
{
	type = AABBType::Circle;
	SetCollider();
}



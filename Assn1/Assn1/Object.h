#pragma once
#include "AABB.h"
class Object
{
public:
	AABB collidebox;//충돌 범위를 나타냅니다.
	
	Object();
	~Object();
};


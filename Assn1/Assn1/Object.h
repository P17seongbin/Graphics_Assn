#pragma once
#include "AABB.h"
class Object
{
public:
	AABB* collidebox;//충돌 범위를 나타냅니다.
	
	Object();
	~Object();
	virtual void Draw() = 0;//이 오브젝트를 화면 상에 그리는 함수입니다.모든 오브젝트에 대해 구현해야만 합니다.
	virtual void Step(float dt) = 0;//매 프레임마다 할 행동을 나타냅니다. dt는 이전 프레임과 현재 프레임의 시간 차이를 나타냅니다.
	virtual void onCollide(Object* other) = 0;//다른 Object와 충돌한 상황을 나타냅니다. 

	const std::pair<float, float> getPos() { return pos; }
	void setPos(float x, float y) { pos.first = x; pos.second = y; }
	void addPos(float dx, float dy) { pos.first += dx; pos.second += dy; }

	const std::pair<float, float> getSpeed() { return speed; }
	void setSpeed(float vx, float vy) { pos.first = vx; pos.second = vy; }
	void addSpeed(float ax, float ay) { pos.first += ax; pos.second += ay; }

	const std::pair<float, float> getAccel() { return accel; }
	void setAccel(float ax, float ay) { pos.first = ax; pos.second = ay; }

private:
		std::pair<float, float> pos;
		std::pair<float, float> speed;
		std::pair<float, float> accel;
};


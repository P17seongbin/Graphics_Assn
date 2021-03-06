#pragma once
#include <map>
#include <list>
#include <iostream>
class AABB;
bool CheckCollide_RR(AABB *a, AABB *b);
bool CheckCollide_RC(AABB *a, AABB *b);
bool CheckCollide_CR(AABB *a, AABB *b);
bool CheckCollide_CC(AABB *a, AABB *b);

typedef bool(*CollideFunctionptr)(AABB *self, AABB *other);

enum AABBType
{
	Circle = 0,
	Rect = 1
};

class AABB
{
public:
	const AABBType getType() { return type; }//AABB의 타입을 리턴
	bool IsCollide(AABB *other) {
		//std::cout << other->getType();
		//printf("%d ", collidechecker[other->getType()](this,other));
		return collidechecker[other->getType()](this,other);
	};//다른 AABB와 충돌했는지 검사합니다
	const std::pair<float, float> getPos() { return pos; }
	void setPos(float x, float y) { pos.first = x; pos.second = y; }
	void setType(int i) { if (i == 0) type = Circle; else type = Rect; }
protected:
	std::pair<float, float> pos;
	AABBType type;

	std::map<AABBType, CollideFunctionptr> collidechecker;
};

class RectAABB : public AABB
{
public:
	RectAABB();
	RectAABB(float x, float y, float first, float second);
	void SetCollider();
	const std::pair<float, float> getSize() { return size; }
	void setSIze(float x, float y) { size.first = x; size.second = y; }
private:
	std::pair<float, float> size;
};

class CircleAABB : public AABB
{
public:
	CircleAABB();
	CircleAABB(float rad, float x, float y);
	void SetCollider();
	const float getRadius() { return r; }
	void setRadius(float R) { r = R; }
private:
	float r;
};


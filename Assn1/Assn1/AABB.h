#pragma once
#include <map>
#include <list>

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
	const AABBType getType() { return type; }//AABB�� Ÿ���� ����
	bool IsCollide(AABB *other) {
		return collidechecker[other->getType()];
	};//�ٸ� AABB�� �浹�ߴ��� �˻��մϴ�

	const std::pair<float, float> getPos() { return pos; }
	void setPos(float x, float y) { pos.first = x; pos.second = y; }

protected:
	std::pair<float, float> pos;
	AABBType type;
	std::map<AABBType, CollideFunctionptr> collidechecker;
};

class RectAABB : public AABB
{
public:
	RectAABB();
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
	void SetCollider();

	const float getRadius() { return r; }
	void setRadius(float R) { r = R; }

private:
	float r;
};


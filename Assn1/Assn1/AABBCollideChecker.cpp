#include "AABB.h"
#include <cmath>
float getDist(std::pair<float, float> p1, std::pair<float, float> p2);
float max(float a, float b) { return a > b ? a : b; }
float min(float a, float b) { return a > b ? b : a; }
std::pair<float, float>& operator-(std::pair<float, float> &a, std::pair<float, float> &b);
std::pair<float, float>& operator+(std::pair<float, float> &a, std::pair<float, float> &b);

float clamp(float value, float lower_bound, float upper_bound) {
	return max(lower_bound, min(upper_bound, value));
}
void RectAABB::SetCollider()
{
	collidechecker[AABBType::Circle] = CheckCollide_RC;
	collidechecker[AABBType::Rect] = CheckCollide_RR;
}

void CircleAABB::SetCollider()
{
	collidechecker[AABBType::Circle] = CheckCollide_CC;
	collidechecker[AABBType::Rect] = CheckCollide_CR;
}

//Rect-Rect
bool CheckCollide_RR(AABB *a, AABB *b)
{
	RectAABB *A = (RectAABB*)a;
	RectAABB *B = (RectAABB*)b;
	std::pair<float, float> posA = A->getPos(), posB = B->getPos();
	std::pair<float, float> sizeA = A->getSize(), sizeB = B->getSize();

	bool colX = posA.first + sizeA.first >= posB.first && posB.first + sizeB.first >= posB.first;
	bool colY = posA.second + sizeA.second >= posB.second && posB.second + sizeB.second >= posB.second;
	return colX && colY;
}
//Circle-Rect
bool CheckCollide_CR(AABB *a, AABB *b)
{
	CircleAABB *A = (CircleAABB*)a;
	RectAABB *B = (RectAABB*)b;

	//B->setSIze(10, 30);
	std::pair<float, float> posA = A->getPos(), posB = B->getPos();
	std::pair<float, float> sizeB = B->getSize();
	std::pair<float, float> diff = posA - posB;
	std::pair<float,float> clamped = 
		std::make_pair(clamp(diff.first,(-0.5f)*sizeB.first,(0.5f)*sizeB.first),clamp(diff.second, (-0.5f)*sizeB.second, (0.5f)*sizeB.second));
	std::pair<float, float> closest = posB + clamped;
	diff = closest - posA;
	return sqrt(pow(diff.first, 2) + pow(diff.second, 2)) < A->getRadius();

}
//Rect-Circle
bool CheckCollide_RC(AABB *a, AABB *b)
{
	return CheckCollide_CR(b, a);
}
//CIrcle-Circle
bool CheckCollide_CC(AABB *a,AABB *b)
{
	CircleAABB *A = (CircleAABB*)a;
	CircleAABB *B = (CircleAABB*)b;
	float dist = getDist(A->getPos(), B->getPos());
	return dist <= (A->getRadius() + B->getRadius());
}
//pair operator+
std::pair<float, float>& operator+(std::pair<float, float> &a, std::pair<float, float> &b)
{
	std::pair<float, float> res = std::make_pair(a.first + b.first, a.second + b.second);
	return res;
}
//pair operator-
std::pair<float, float>& operator-(std::pair<float, float> &a, std::pair<float, float> &b)
{
	std::pair<float, float> res = std::make_pair(a.first - b.first, a.second - b.second);
	return res;
}
float getDist(std::pair<float, float> p1, std::pair<float, float> p2)
{
	return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}
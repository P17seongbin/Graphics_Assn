#pragma once
#include "Object.hpp"
#define PI 3.14151

class Player : public Object
{
public:
	Player(KeyHandler* handler,bool _1P);

	void Step(int dt) override;
	void Draw() override;
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override;
	void updateAABB()
	{
		//collidebox[1]->setPos(center_x, center_y);
		collidelist[0]->setPos(pos.first, pos.second);
	}
	void setminMax(float m, float M) { min = m; max = M; }
	void setMin(float val) { min = val; }
	
private:
	//std::pair<float, float> size;
	float head_rad;
	float body;
	float center_x;
	float center_y;
	float min;
	float max;
	bool is_1P;
};

class UnitCircle : public Object
{
public:
	UnitCircle(float posx, float posy, float r, Object* parent) : Object()
	{
		boundary = new CircleAABB(r, 0, 0);
		collidelist.push_back(boundary);
		//std::cout << r;
		setPos(posx, posy);
		setRadius(r);
		Parent = parent;
	}
	UnitCircle();
	void Step(int dt) override;
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override;
	void Draw() override;
	void updateAABB()
	{
		std::pair<float, float> gpos = getGlobalPos();
		//std::cout << gpos.first << " " << gpos.second << std::endl;
		boundary->setPos(gpos.first, gpos.second);
	}
	void setRadius(float r)
	{
		Radius = r;
		boundary->setRadius(r);
	}
	float getRadius() { return Radius; }
private:
	CircleAABB * boundary;
	float Radius;
};

class UnitTri : public Object
{
public:
	UnitTri(float posx, float posy, Object* parent) :Object()
	{
		setPos(posx, posy);
		Parent = parent;
		setSize(12, 3);
	}
	UnitTri();
	void Step(int dt) override;
	void Draw() override;
	//updateAABB not needed

};
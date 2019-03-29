#include "Cloud.h"

Cloud::Cloud(float x, float y,float speed_x)
{
	setPos(x, y);//initial position of cloud
	setSpeed(speed_x, 0);
	setColor(1,1,1);
	move_x = 1;
	wing_speed = 0.2;
	move_y = 1;

	UnitCircle* c = new UnitCircle(0, 0, 5, NULL);
	c->setColor(color.r, color.g, color.b);
	addChild(c);
	UnitCircle* d = new UnitCircle(3, -4, 5, NULL);
	d->setColor(color.r, color.g, color.b);
	addChild(d);
	UnitCircle* e = new UnitCircle(- 3,  - 4, 5, NULL);
	e->setColor(color.r, color.g, color.b);
	addChild(e);

	UnitCircle* a = new UnitCircle(move_x,move_y, 5, NULL);
	a->setColor(color.r, color.g, color.b);
	addChild(a);
	UnitCircle* b = new UnitCircle(-move_x,move_y, 5, NULL);
	b->setColor(color.r, color.g, color.b);
	addChild(b);
}
void Cloud::Draw(void)
{
	Object::Draw();
	for (int i = 0; i < 5; i++) 
	{
		ChildList[i]->Draw();
	}
	glPopMatrix();
}

void Cloud::Step(int dt)
{
	Object::Step(dt);
	//setPos(pos.first + speed.first, pos.second);
	if (pos.first > WIN_HOR || pos.first < 0)
		speed.first = -speed.first;

	move_x = move_x + wing_speed;
	move_y = move_y - wing_speed;
	if (move_x > 5||move_x<1)
	{
		wing_speed = -wing_speed;
	}
	ChildList[3]->setPos(move_x, move_y);
	ChildList[4]->setPos(-move_x, move_y);

	
}

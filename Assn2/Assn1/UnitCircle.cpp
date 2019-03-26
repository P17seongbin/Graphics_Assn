#include "Player.h"

void UnitCircle::Step(int dt)
{
	updateAABB();
}
UnitCircle::UnitCircle()
{
	setPos(0, 0);
}
void UnitCircle::onCollide(Object* other, AABB* selfAABB, AABB* otherAABB)
{
	if (other->tag == "Ball")
	{
		if (Parent->getalpha() == -2)
		{
			Parent->setalpha(2);
		}
	}
}
void UnitCircle::Draw()
{
	glPushMatrix();
	glTranslatef(pos.first, pos.second, 0);
	glColor3f(color.r, color.g, color.b);
	int triangleAmount = 20; //# of triangles used to draw circle

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(0, 0); // center of circle
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			(Radius * cos(i * PI * 2 / triangleAmount)),
			(Radius * sin(i * PI * 2 / triangleAmount))
		);
	}
	glEnd();
	for (int i = 0; i < ChildList.size(); i++) {
		ChildList[i]->Draw();
	}

	glPopMatrix();
}

void Face::Draw()//draw sunglasses
{
	glColor3f(0, 0, 0);
	glRectf(-4, 1, 4, 1.5);
	glRectf(-3.5, -1.5, -0.5, 1.5);
	glRectf(0.5, -1.5, 3.5, 1.5);
	glColor3f(1, 1, 1);
	glRectf(-3, -0.5, -2.5, 1);
	glRectf(1, -0.5, 1.5, 1);
}
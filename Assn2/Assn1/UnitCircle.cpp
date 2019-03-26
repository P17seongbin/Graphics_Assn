#include "Player.h"

void UnitCircle::Step(int dt)
{
	updateAABB();
}
UnitCircle::UnitCircle()
{
	setPos(0, 0);
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

	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glPointSize(20);
	glVertex2f(-1.5, 2);
	glVertex2f(1.5, 2);
	glEnd();

	glPopMatrix();
}
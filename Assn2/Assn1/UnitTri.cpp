#include "Player.h"

void UnitTri::Draw()
{
	//glPushMatrix();
	glPushMatrix();
	glTranslatef(pos.first, pos.second, 0);
	

	glColor3f(color.r, color.g, color.b);
	
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, size.first);
	glVertex2f(-size.second, size.first);
	glEnd();
	
	for (int i = 0; i < ChildList.size(); i++) {
		ChildList[i]->Draw();
	}

	glPopMatrix();
}
void UnitTri::Step(int dt)
{}
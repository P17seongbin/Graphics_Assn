#include "Player.h"

void UnitTri::Draw() 
{
	Object::Draw();

	for (int i = 0; i < ChildList.size(); i++) {
		ChildList[i]->Draw();
	}
	glColor3f(color.r, color.g, color.b);
	
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, size.first);
	glVertex2f(-1 * size.second, size.first);
	glEnd();
	glPopMatrix();
}
void UnitTri::Step(int dt)
{

}

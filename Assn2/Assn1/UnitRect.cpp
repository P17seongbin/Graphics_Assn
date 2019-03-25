#include "Net.h"

UnitRect::UnitRect(float x, float y, float height, float width)
{
	setPos(x, y);
	setSize(height,width);
	collidebox.push_back(new RectAABB(x, y, height, width));
}

void UnitRect::Draw()
{
	glPushMatrix();
	glTranslatef(pos.first, pos.second,0);
	
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(0,size.first);
	glVertex2f(size.second,size.first);
	glVertex2f(size.second,0);
	glEnd();

	glPopMatrix();
}

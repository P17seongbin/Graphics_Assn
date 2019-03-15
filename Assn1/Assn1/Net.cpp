#include "Net.h"

Net::Net(float x, float y, float height, float width)
{
	setPos(x, y);
	setSize(height,width);
	tag = "Net";
	collidebox.push_back(new RectAABB(x, y, height, width));
}

void Net::Draw()
{
	glColor3f(1.0,1,1);
	glBegin(GL_POLYGON);
	glVertex2f(pos.first, pos.second);
	glVertex2f(pos.first, pos.second + size.first);
	glVertex2f(pos.first + size.second, pos.second + size.first);
	glVertex2f(pos.first + size.second, pos.second);
	glEnd();
}

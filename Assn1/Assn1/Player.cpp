#include "Player.h"

const float DEG2RAD = 3.14159 / 180;

void Player::Draw()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.5, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(pos.first, pos.second);
	glVertex2f(pos.first, pos.second + size.first);
	glVertex2f(pos.first + size.second, pos.second + size.first);
	glVertex2f(pos.first + size.second, pos.second);
	glVertex2f(pos.first + size.second, pos.second + size.first);

	glEnd();
}

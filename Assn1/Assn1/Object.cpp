#include "Object.h"
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

void Ball::Step(int dt) {
	if (pos.first < 0 || pos.first > 100) speed = std::make_pair(speed.first * -1, speed.second);
	if (pos.second < 0 || pos.second > 100)  speed = std::make_pair(speed.first, speed.second * -1);
	addPos(speed.first * dt, speed.second * dt);
}
void Ball::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(pos.first, pos.second);
	glVertex2f(pos.first, pos.second + radius);
	glVertex2f(pos.first + radius, pos.second +radius);
	glVertex2f(pos.first + radius, pos.second);
	glEnd();

}
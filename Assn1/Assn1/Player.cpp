#include "Player.h"
#include "System.h"
const float DEG2RAD = 3.14159 / 180;

Player::Player(KeyHandler *handler,bool _1P)
{
	keyhandler = handler;
	tag = "Player";
	setSize(30, 10);
	setSpeed(0, 0);
	is_1P = _1P;
	AABB rect;
	rect.setType(1);
	rect.setPos(0, 0);
	collidebox.push_back(&rect);//�̰ųִ¼��� �ȵ�(ball������ �־ ���ư�)
}

void Player::Draw()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(pos.first, pos.second);
	glVertex2f(pos.first, pos.second + size.first);
	glVertex2f(pos.first + size.second, pos.second + size.first);
	glVertex2f(pos.first + size.second, pos.second);
	glVertex2f(pos.first + size.second, pos.second + size.first);
	
	glEnd();
}
void Player::Step(int dt)
{
	//BAAAAAAAAAAAD code!
	if (is_1P)
	{
		if (keyhandler->isAsciiKeyPressed('z'))
			setSpeed(-1 * SPEED, 0);
		else if (keyhandler->isAsciiKeyPressed('c'))
			setSpeed(SPEED, 0);
		else setSpeed(0, 0);
	}
	else
	{
		if (keyhandler->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			setSpeed(-1 * SPEED, 0);
		}
		else if (keyhandler->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			setSpeed(SPEED, 0);
		}
		else setSpeed(0, 0);
	}
	updateAABB();
	Move(dt);
}
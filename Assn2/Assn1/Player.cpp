#include "Player.h"
#include "System.h"
//#include "Ear.hpp"
const float DEG2RAD = 3.14159f / 180;

Player::Player(KeyHandler *handler,bool _1P)
{
	Parent = NULL;
	keyhandler = handler;
	tag = "Player";
	setSize(30,15);
	body=size.first-1.5*head_rad;

	setSpeed(0, 0);
	is_1P = _1P;
	min = (!is_1P) * 50;
	max = min + 50 - size.second;
	collidelist.push_back(new RectAABB(0,0,body,15));

	alpha = -2;
}

void Player::onCollide(Object* other, AABB* selfAABB, AABB* otherAABB)
{
}

void Player::Draw() 
{
	Object::Draw();
	//glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(0,body);
	glVertex2f(size.second,body);
	glVertex2f(size.second,0);

	glEnd();
	
	for (int i = 0; i < ChildList.size(); i++) {
		ChildList[i]->Draw();
	}
	glPopMatrix();
}
void Player::Step(int dt)
{
	if (is_1P)
	{
		if (keyhandler->isAsciiKeyPressed('z') || keyhandler->isAsciiKeyPressed('Z'))
			setSpeed(-1 * SPEED, 0);
		else if (keyhandler->isAsciiKeyPressed('c') || keyhandler->isAsciiKeyPressed('C'))
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

	if (pos.first < min)
		setPos(min, 0);
	if (pos.first > max)
		setPos(max, 0);

	updateAABB();
	Move(dt);

	for (int i = 0; i < ChildList.size(); i++) {
		ChildList[i]->Step(dt);
		if (ChildList[i]->tag == "tail" || ChildList[i]->tag == "ear")
			ChildList[i]->setAngle((alpha + 2) * 7.5 + 15);
	}
	if (alpha !=-2)
	{

		alpha--;
	}
}

#include "Player.h"
#include "System.h"
const float DEG2RAD = 3.14159f / 180;

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
	int triangleAmount = 20; //# of triangles used to draw circle

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 0.2);
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
	glPointSize(5);
	glVertex2f(-1.5,2);
	glVertex2f(1.5, 2);
	glEnd();

	glPopMatrix();
}
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
	collidebox.push_back(new RectAABB(0,0,body,15));
}

void Player::onCollide(Object* other, AABB* selfAABB, AABB* otherAABB)
{
}

void Player::Draw()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(pos.first, pos.second, 0);
	glColor3f(1, 1, 0.2);

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

	if (pos.first < min)
		setPos(min, 0);
	if (pos.first > max)
		setPos(max, 0);
	updateAABB();
	Move(dt);

	for (int i = 0; i < ChildList.size(); i++) {
		ChildList[i]->Step(dt);
	}
}

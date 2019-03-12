#include "Player.h"
#include "System.h"
const float DEG2RAD = 3.14159 / 180;

Player::Player(KeyHandler *handler,bool _1P)
{
	keyhandler = handler;
	tag = "Player";
	setSize(30,15);
	head_rad = 0.4*size.first / 2;
	body=size.first-1.5*head_rad;
	center_x = pos.first + size.second / 2;
	center_y = size.first - head_rad;
	setSpeed(0, 0);
	is_1P = _1P;
	collidebox.push_back(new RectAABB(0,0,body,15));
	collidebox.push_back(new CircleAABB(head_rad, 0, 0));
}

void Player::Draw()
{
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(pos.first, pos.second);
	glVertex2f(pos.first, pos.second + body);
	glVertex2f(pos.first + size.second, pos.second + body);
	glVertex2f(pos.first + size.second, pos.second);
	//GLfloat radius = 0.8f; //radius
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(center_x,center_y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			center_x+ (head_rad * cos(i *  twicePi / triangleAmount)),
			center_y + (head_rad * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	glColor3f(0, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(center_x-1.5,center_y+2);
	glVertex2f(center_x + 1.5, center_y+2);
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
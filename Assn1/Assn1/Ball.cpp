#include "Ball.h"
#define PI 3.1415

Ball::Ball()
{
	tag = "Ball";
	setRadius(5.0);
	setSpeed(0.050, 0.050);
	setPos(70, 50);
	collidebox.push_back(new CircleAABB(radius,pos.first,pos.second));
}
void Ball::Step(int dt) {

	if (pos.first < radius || pos.first > 100-radius) speed = std::make_pair(speed.first * -1, speed.second);
	if (pos.second < radius || pos.second > 100-radius)  speed = std::make_pair(speed.first, speed.second * -1);
	updateAABB();
	Move(dt);
}

void Ball::onCollide(Object* other, AABB* selfAABB, AABB* otherAABB)
{	
		if (pos.second > other->getSize().first)
		{
			if (speed.second < 0)
				setSpeed(speed.first, -speed.second);
		}
		if (pos.first <= other->getPos().first)
		{
			if (speed.first > 0)
				setSpeed(-speed.first, speed.second);
		}
		if (pos.first >= (other->getPos().first) + (other->getSize().second))
		{
			if (speed.first < 0)
				setSpeed(-speed.first, speed.second);
		}
}
void Ball::Draw()
{
	//(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = RADIUS * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(pos.first, pos.second); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			pos.first + (radius * cos(i *  twicePi / triangleAmount)),
			pos.second + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
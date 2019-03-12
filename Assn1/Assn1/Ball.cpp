#include "Ball.h"
#define PI 3.1415
Ball::Ball()
{
	tag = "Ball";
	setRadius(1.0);
	setSpeed(0.2, 0.15);
	collidebox.push_back(new CircleAABB(radius,pos.first,pos.second));
}
void Ball::Step(int dt) {
	if (pos.first < 0 || pos.first > 100) speed = std::make_pair(speed.first * -1, speed.second);
	if (pos.second < 0 || pos.second > 100)  speed = std::make_pair(speed.first, speed.second * -1);
	updateAABB();
	Move(dt);
}

void Ball::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

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
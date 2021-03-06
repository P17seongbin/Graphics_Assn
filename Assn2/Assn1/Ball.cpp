#include "Ball.h"
#include <cmath>
#define PI 3.1415
Ball::Ball()
{
	tag = "Ball";
	setRadius(RADIUS);
	setSpeed(SPEED,SPEED);
	setPos(70, 50);
	setAnchor(0,0);
	collidelist.push_back(new CircleAABB(radius,pos.first,pos.second));
}
void Ball::Step(int dt) {

	updateAABB();
	Object::Step(dt);
	
	float dangle = 15;
	if (pos.first < radius)
	{
		setPos(radius, pos.second);
		setSpeed(speed.first * -1, speed.second);
	}
	if (pos.first > 100 - radius)
	{
		setPos(100 - radius, pos.second);
		setSpeed(speed.first * -1, speed.second);
	}
	angle += dangle;
	if (angle >= 360) angle -= 360;
}
void Ball::onCollide(Object* other, AABB* selfAABB, AABB* otherAABB)
{
	if (other->tag == "h1" || other->tag == "player1")
	{
		IsCollidedwithP1 = true;
	}
	//selfAABB는 언제나 원형!
	if (otherAABB->getType() == AABBType::Rect)
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
	//원형 AABB에 충돌한 경우
	else
	{
		std::pair<float, float> d = std::make_pair(selfAABB->getPos().first - otherAABB->getPos().first, selfAABB->getPos().second - otherAABB->getPos().second);
		double angle = atan2(d.second, d.first);
		double c = cos(angle);
		double s = sin(angle);
		if (c*speed.first + s * speed.second < 0)
		{
			std::pair<float, float> newspeed = std::make_pair(
				(pow(s, 2) - pow(c, 2)) * speed.first - (2.0 * c * s * speed.second),
				(pow(c, 2) - pow(s, 2)) * speed.second - (2.0 * c * s * speed.first));
			//std::cout << angle << " " << d.first << " " << d.second << " " << speed.first << " " << speed.second << std::endl;
			setSpeed(newspeed.first, newspeed.second);
		}
	}
}
void Ball::Draw()
{
	Object::Draw();
	glColor3f(color.r, color.g, color.b);
	int triangleAmount = 20; //# of triangles used to draw circle
	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(0,0); // center of circle
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			(radius * cos(i * 2 * PI / triangleAmount)),
			(radius * sin(i * 2 * PI / triangleAmount))
		);
	}
	glEnd();
	Draw_Electricity();
	glPopMatrix();
}

void Ball::Draw_Electricity()
{
	float dangle = 15;
	float cangle = 30;
	float line_len = radius / 2;
	int line_count = 10;
	glPushMatrix();
	//rotate
	glRotatef(angle, 0,0,1);
	glTranslatef(0, -1 * radius, 0);
	glColor3f(1,1,0);
	for (int i = 0; i < line_count; i++)
	{
		if (i % 2 == 0)
		{
			glRotatef(dangle, 0, 0, 1);
		}
		else
		{
			glRotatef(180 - 2 * cangle, 0, 0,1);
		}
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0,line_len);
		glEnd();
		glTranslatef(0,line_len, 0);
		if (i % 2 == 1)
		{
			glRotatef(180 - dangle, 0, 0, -1);
		}
	}
	glPopMatrix();
}

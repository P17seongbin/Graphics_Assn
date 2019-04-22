#include "ball.h"



Ball::Ball(RenderChannel * channel)
{
	glm::vec3 initialPos = glm::vec3(0, 0, 0);
	glm::vec3 initialSpeed = glm::vec3(0, 0, 0.01);
	setTag("ball");
	setDir(0);
	setPos(initialPos);
	setSpeed(initialSpeed);
	setobjID(1);
	Channel = channel;
}

void Ball::update(GLFWwindow* window, float dt)
{
	addPos(Speed);
	//printf("%f %f %f", Speed[0], Speed[1], Speed[2]);
	if (Pos[0] > FIELD_WIDTH / 2 || Pos[0] <-FIELD_WIDTH/2)
	{
		Speed[0] = -Speed[0];
	}

	if (Pos[2] > FIELD_LENGTH/2 || Pos[2]<-FIELD_LENGTH/2) //OUT OF BOUNDARY
	{
		Speed[2] = -Speed[2];
		//Pos[2] = FIELD_LENGTH / 2;
	}
}
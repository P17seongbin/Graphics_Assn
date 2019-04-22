#include "AIPlayer.h"


AIPlayer::AIPlayer(RenderChannel * channel)
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, (float)FIELD_LENGTH / 2);
	glm::vec3 initialSpeed = glm::vec3(0, 0, 0);
	setTag("player2");
	setPos(initialPos);
	setSpeed(initialSpeed);
	setDir(0);
	
	Channel = channel;
}

void AIPlayer::update(GLFWwindow* window,float ball_x)
{
	float posx = Pos[0];
	float dspeedx = 0.005;

	if (ball_x > posx)
	{
		addDir(0.01f);
		addSpeed(glm::vec3(dspeedx, 0, 0));
	}
	else {
		addDir(-0.01f);
		addSpeed(glm::vec3(-dspeedx, 0, 0));
	}
	//printf("%f", posx);
	addPos(Speed);


	if (Pos[0] > FIELD_WIDTH / 2)
	{
		Pos[0] = FIELD_WIDTH / 2;
	}
	else if (Pos[0] < (-1)*FIELD_WIDTH / 2)
	{
		Pos[0] = -FIELD_WIDTH / 2;
	}
	Pos[1] = 0;
	Pos[2] = (float)FIELD_LENGTH / 2;
}
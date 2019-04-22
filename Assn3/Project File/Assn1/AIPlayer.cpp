#include "AIPlayer.h"

AIPlayer::AIPlayer(RenderChannel* channel)
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, 0.5*(float)FIELD_LENGTH);
	glm::vec3 initialSpeed = glm::vec3(0, 0, 0);
	setTag("player2");
	setPos(initialPos);
	setDir(3.14);
	setobjID(0);
	setSpeed(initialSpeed);
	Channel = channel;
}

void AIPlayer::Move(float dt)
{
	Pos = (Pos + (Speed * dt) + (0.5f * Accel * dt * dt));
	Speed = (Speed + Accel * dt);
}

void AIPlayer::update(GLFWwindow* window, float dt)
{
	float dxspeed = 1;
	float max = 0.01;
	float ds = 0.1f;
	//각도가 0일때 +z축, 각도가 180일때 -z축
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		setSpeed(glm::vec3(dxspeed * sinf(Dir), 0, dxspeed * cosf(Dir)));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		setSpeed(glm::vec3(dxspeed * sinf(Dir) * -1, 0, dxspeed * cosf(Dir) * -1));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{
		setSpeed(glm::vec3(0, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		addDir(-0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		addDir(0.01f);
	}


	Move(dt);
	if (Pos[0] > FIELD_WIDTH / 2)
	{
		Pos[0] = FIELD_WIDTH / 2;// setPos(glm::vec3(FIELD_WIDTH / 2, 0, 0));
	}
	else if (Pos[0] < (-1)*FIELD_WIDTH / 2)
	{
		Pos[0] = -FIELD_WIDTH / 2;//setPos(glm::vec3(-FIELD_WIDTH / 2, 0, 0));
	}
}
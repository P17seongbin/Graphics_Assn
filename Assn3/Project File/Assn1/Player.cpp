#include "GameManager.h"
#include "Player.h"
Player::Player(RenderChannel* channel)
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, -0.25f * (float)FIELD_LENGTH);
	glm::vec3 initialSpeed = glm::vec3(0, 0, 0);
	setTag("player1");
	setPos(initialPos);
	setDir(0);
	setobjID(0);
	setSpeed(initialSpeed);
	Channel = channel;
}
void Player::Move(float dt)
{
	Pos = (Pos + (Speed * dt) + (0.5f * Accel * dt * dt));
	Speed = (Speed + Accel * dt);
}
void Player::update(GLFWwindow* window,float dt) {
	
	float dxspeed = 1;
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
		Pos[0] = FIELD_WIDTH/2;
	else if (Pos[0] < (-1)*FIELD_WIDTH / 2)
		Pos[0] = -FIELD_WIDTH / 2;

	if (Pos[2] < -FIELD_LENGTH / 2)
		Pos[2] = -FIELD_LENGTH / 2;
	else if (Pos[2] >= 0)
		Pos[2] = 0;
}

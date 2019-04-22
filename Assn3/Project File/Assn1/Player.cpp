#include "Player.h"

Player::Player(RenderChannel* channel)
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, 0.0);
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
	
	float dxspeed = 0.0005;
	float max = 0.01;
	float ds = 0.1f;
	//������ 0�϶� +x��, ������ 90�϶� +z��
	//test �غ��ߵ�
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		addDir(0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		addDir(-0.01f);
	}

	Move(dt);
	if (Pos[0] > FIELD_WIDTH / 2)
	{
		Pos[0] = FIELD_WIDTH/2;// setPos(glm::vec3(FIELD_WIDTH / 2, 0, 0));
	}
	else if (Pos[0] < (-1)*FIELD_WIDTH / 2)
	{
		Pos[0] = -FIELD_WIDTH / 2;//setPos(glm::vec3(-FIELD_WIDTH / 2, 0, 0));
	}
}

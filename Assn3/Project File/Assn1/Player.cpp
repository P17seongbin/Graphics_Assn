#include "Player.h"

Player::Player()
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 initialSpeed = glm::vec3(0, 0, 0);
	//glm::vec3 initialDir = glm::vec3(0, 0, 1);
	setTag("player1");
	setPos(initialPos);
	//setDir(initialDir);
	setSpeed(initialSpeed);
}
void Player::update(GLFWwindow* window) {
	
	float dxspeed = 0.00005;
	float max = 0.01;

	//test 해봐야됨
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		addPos(Speed);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		addPos(-Speed);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//너무 빨라지면 안되니까 일단 max 잡겟음
		if(max>Speed[0])
			addSpeed(glm::vec3(dxspeed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (-max<Speed[0])
			addSpeed(glm::vec3(-dxspeed, 0, 0));
	}

	if (Pos[0] > FIELD_WIDTH / 2)
	{
		Pos[0] = FIELD_WIDTH/2;// setPos(glm::vec3(FIELD_WIDTH / 2, 0, 0));
	}
	else if (Pos[0] < (-1)*FIELD_WIDTH / 2)
	{
		Pos[0] = -FIELD_WIDTH / 2;//setPos(glm::vec3(-FIELD_WIDTH / 2, 0, 0));
	}

	// player의 y,z좌표는 0으로 고정
	Pos[1] = 0;
	Pos[2] = 0;
}

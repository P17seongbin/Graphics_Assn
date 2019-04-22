#include "Player.h"

Player::Player(RenderChannel* channel)
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, -(float)FIELD_LENGTH/ 2);
	glm::vec3 initialSpeed = glm::vec3(0, 0, 0);
	setTag("player1");
	setPos(initialPos);
	setDir(0);
	setSpeed(initialSpeed);

	Channel = channel;
}
void Player::update(GLFWwindow* window,float ball_x) {
	
	float dxspeed = 0.00005;
	float max = 0.01;
	
	float ds = 0.1f;
	//각도가 0일때 +x축, 각도가 90일때 +z축
	//test 해봐야됨
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//glm::vec3 dPos(cosf(getDir()) * ds, sinf(getDir()) * ds,0);
		//addPos(dPos);
		addPos(Speed);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		addPos(-Speed);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		addDir(0.01f);
		//너무 빨라지면 안되니까 일단 max 잡겟음
		if(max>Speed[0])
			addSpeed(glm::vec3(dxspeed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		addDir(-0.01f);
		if (-max<Speed[0])
			addSpeed(glm::vec3(-dxspeed, 0, 0));
	}

	if (Pos[0] > FIELD_WIDTH / 2)
	{
		Pos[0] = FIELD_WIDTH/2;
	}
	else if (Pos[0] < (-1)*FIELD_WIDTH / 2)
	{
		Pos[0] = -FIELD_WIDTH / 2;
	}

	// player의 y,z좌표는 0으로 고정
	Pos[1] = 0;
	Pos[2] = (float)FIELD_LENGTH / 2;
}

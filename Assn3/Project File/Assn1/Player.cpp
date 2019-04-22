#include "Player.h"

Player::Player(RenderChannel* channel)
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 initialSpeed = glm::vec3(0, 0, 0);
	//glm::vec3 initialDir = glm::vec3(0, 0, 1);
	setTag("player1");
	setPos(initialPos);
	setDir(0);
	setobjID(0);
	//setDir(initialDir);
	setSpeed(initialSpeed);

	Channel = channel;
}
void Player::update(GLFWwindow* window) {
	
	float dxspeed = 0.00005;
	float max = 0.01;
	
	float ds = 0.1f;
	//������ 0�϶� +x��, ������ 90�϶� +z��
	//test �غ��ߵ�
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
		//�ʹ� �������� �ȵǴϱ� �ϴ� max �����
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
		Pos[0] = FIELD_WIDTH/2;// setPos(glm::vec3(FIELD_WIDTH / 2, 0, 0));
	}
	else if (Pos[0] < (-1)*FIELD_WIDTH / 2)
	{
		Pos[0] = -FIELD_WIDTH / 2;//setPos(glm::vec3(-FIELD_WIDTH / 2, 0, 0));
	}

	// player�� y,z��ǥ�� 0���� ����
	Pos[1] = 0;
	Pos[2] = 0;
}

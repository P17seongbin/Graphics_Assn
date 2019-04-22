#include "AIPlayer.h"


AIPlayer::AIPlayer(RenderChannel * channel)
{
	glm::vec3 initialPos = glm::vec3(0.0, 0.0, (float)FIELD_LENGTH);
	//glm::vec3 initialDir = glm::vec3(0, 0, -1);
	setTag("player2");
	setPos(initialPos);
	//setDir(initialDir);
}

void AIPlayer::update(GLFWwindow* window, float dt)
{

}
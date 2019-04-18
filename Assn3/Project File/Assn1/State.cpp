#include "State.h"

GLuint State::getCameraID()
{
	return GLuint();
}

GLuint State::getShaderID()
{
	return GLuint();
}

int State::getPlayerScore()
{
	return 0;
}

int State::getAIScore()
{
	return 0;
}

bool State::setCameraID(GLuint ID)
{
	return false;
}

bool State::setShaderID(GLuint ID)
{
	return false;
}

bool State::CameraControl(CameraMovement dir)
{
	return false;
}

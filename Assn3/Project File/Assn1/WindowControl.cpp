#include "Assn2.h"

void ReShape(int w, int h)
{
	glLoadIdentity(); //Stack matrix = I
	gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
	glViewport(0, 0, w, h);
}

void setOrtho2D(GameManager* GM,KeyHandler* keyhandler)
{
	glLoadIdentity();
	if (keyhandler->isAsciiKeyPressed('x'))
	{
		std::pair<float, float> pos = GM->findObjectwithTag("ball")->getPos();//���̶�� �±׸� ���� ������Ʈ�� �����ɴϴ�.

		//Window�� ��ǥ�� �����մϴ�.
		pos = make_pair(
			MAX(MIN(WIN_HOR - CAM_SIZE, pos.first), CAM_SIZE),
			MAX(MIN(WIN_VER - CAM_SIZE, pos.second), CAM_SIZE)
		);
		//Cam�� ���� ��ǥ���� ������ Size�� Window�� �����մϴ�.
		gluOrtho2D(pos.first - CAM_SIZE, pos.first + CAM_SIZE, pos.second - CAM_SIZE, pos.second + CAM_SIZE);
	}
	else
		gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
}
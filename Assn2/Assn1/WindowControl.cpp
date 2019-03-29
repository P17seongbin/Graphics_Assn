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
		std::pair<float, float> pos = GM->findObjectwithTag("ball")->getPos();//공이라는 태그를 가진 오브젝트를 가져옵니다.

		//Window의 좌표를 설정합니다.
		pos = make_pair(
			MAX(MIN(WIN_HOR - CAM_SIZE, pos.first), CAM_SIZE),
			MAX(MIN(WIN_VER - CAM_SIZE, pos.second), CAM_SIZE)
		);
		//Cam의 계산된 좌표에서 정해진 Size로 Window를 생성합니다.
		gluOrtho2D(pos.first - CAM_SIZE, pos.first + CAM_SIZE, pos.second - CAM_SIZE, pos.second + CAM_SIZE);
	}
	else
		gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
}
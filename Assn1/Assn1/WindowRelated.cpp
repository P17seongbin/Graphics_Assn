#include "Assn1.h"

void ReShape(int w, int h)
{
	glLoadIdentity(); //Stack matrix = I
	glViewport(0, 0, w, h);
	
	gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
	glTranslatef(10, 10, 0);
	
	
}

void setOrtho2D(GameManager* GM,KeyHandler* keyhandler)
{
	glLoadIdentity();
	if (keyhandler->isAsciiKeyPressed('x'))
	{
		std::pair<float, float> pos = GM->findObjectwithTag("ball")->getPos();//공이라는 태그를 가진 오브젝트를 가져옵니다.
		float size = CAM_SIZE;
		pos = make_pair(
			MAX(MIN(WIN_HOR - size, pos.first), size),
			MAX(MIN(WIN_VER - size, pos.second), size)
		);
		gluOrtho2D(pos.first - size, pos.first + size, pos.second - size, pos.second + size);
	}
	else
		gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
}
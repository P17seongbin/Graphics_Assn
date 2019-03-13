#include "System.h"
#include <algorithm>
#include "Ball.h"
#include "Player.h"
#include <GL/glew.h>
#include <GL/freeglut.h> 
GameManager::GameManager()
{
	//Init AABB's Collider Function Point vector
	l = 0;
}
void GameManager::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (std::vector<std::pair<std::string, Object*>>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
	{
		it->second->Draw();
	}
	glutPostRedisplay();
	glutSwapBuffers();
}
void GameManager::Step(int dt)
{
	//1. 오브젝트 충돌 판정
	Object* ball = getObjectList()[2].second;;
	std::pair<float,float> pos=ball->getPos();
	

	calCollide();
	//2. 각 Object의 Step을 호출
	for (std::vector<std::pair<std::string, Object*>>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
	{
		it->second->Step(dt);
	}
	
	if (pos.second < ball->getRadius())
	{
		if (pos.first < 50)
			score_2++;
		else score_1++;

		printf("/%d %d", score_1, score_2);
	}
	
	//3. 죽은 오브젝트에 대한 데이터를 말소
	//ObjectList.erase(std::remove_if(ObjectList.begin(), ObjectList.end(), [](std::pair<std::string, Object*> &v) { return v.second->isDestroy(); }));
	//ObjectList.shrink_to_fit();
	Draw();
}

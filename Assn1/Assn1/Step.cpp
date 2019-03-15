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
void drawBitmapText(std::string string, float x, float y, float z)
{
	glRasterPos2f(x, y);
	for (int i=0;i<string.length();i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void GameManager::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (std::vector<std::pair<std::string, Object*>>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
	{
		it->second->Draw();
	}
	glColor3f(0, 0, 0);//�� ����,���� 7-segment�� �����
	drawBitmapText(std::to_string(score_1),10,80,0); 
	drawBitmapText(std::to_string(score_2), 88, 80, 0);
	

	glutPostRedisplay();
	glutSwapBuffers();
}
void GameManager::Step(int dt)
{
	//1. ������Ʈ �浹 ����
	Object* ball = getObjectList()[2].second;;
	std::pair<float,float> pos=ball->getPos();
	
	calCollide();
	//2. �� Object�� Step�� ȣ��
	for (std::vector<std::pair<std::string, Object*>>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
	{
		it->second->Step(dt);
	}
	
	if (pos.second < ball->getRadius())
	{
		if (pos.first < 50)
			score_2++;
		else score_1++;
	}
	
	//3. ���� ������Ʈ�� ���� �����͸� ����
	//ObjectList.erase(std::remove_if(ObjectList.begin(), ObjectList.end(), [](std::pair<std::string, Object*> &v) { return v.second->isDestroy(); }));
	//ObjectList.shrink_to_fit();
	Draw();
}
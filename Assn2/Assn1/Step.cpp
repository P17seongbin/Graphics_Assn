#include "System.h"
#include <algorithm>
#include "Ball.h"
#include "Player.h"
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "Assn2.h"
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
	int max = 15;
	int size = 30;
	int winner = 1;

	glClear(GL_COLOR_BUFFER_BIT);
	if (score_1 == max || score_2 == max) //game over
	{
		ObjectList[2].second->setSpeed(0, 0);//stop ball

		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 0.5, 0.2);
		glBegin(GL_POLYGON);//draw 'window'
		glVertex2f(WIN_HOR / 2 - size, WIN_VER / 2 - size);
		glVertex2f(WIN_HOR / 2 - size, WIN_VER / 2 + size);
		glVertex2f(WIN_HOR / 2 + size, WIN_VER / 2 + size);
		glVertex2f(WIN_HOR / 2 + size, WIN_VER / 2 - size);
		glEnd();

		glColor3f(0, 0, 0);//print message
		if (score_1 == max)
		{
			drawBitmapText("You WIN!!", WIN_HOR / 2-6, WIN_VER / 2,0);
		}
		else
		{
			drawBitmapText("You LOSE!!", WIN_HOR / 2-6, WIN_VER / 2, 0);
		}

	}
	else {
		for (std::vector<std::pair<std::string, Object*>>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
		{
			if (it->second->getParent() == NULL)
			it->second->Draw();
		}
		glColor3f(0, 0, 0);
		drawBitmapText(std::to_string(score_1), 10, 80, 0);
		drawBitmapText(std::to_string(score_2), 88, 80, 0);
	}
	glutPostRedisplay();
	glutSwapBuffers();
}
void GameManager::Step(int dt)
{
	//1. 오브젝트 충돌 판정
	Object* ball = getObjectList()[2].second;;
	std::pair<float,float> pos=ball->getPos();
	float newy = WIN_VER/2;

	calCollide();
	//2. 각 Object의 Step을 호출
	for (std::vector<std::pair<std::string, Object*>>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
	{
		if(it->second->getParent() == NULL)
		it->second->Step(dt);
	}
	
	if (pos.second < ball->getRadius())
	{

		if (pos.first < WIN_HOR / 2)
		{
			score_2++;
			ball->setSpeed(SPEED, -SPEED);
		}
		else
		{
			score_1++;
			ball->setSpeed(-SPEED, -SPEED);
		}

		newy += rand() % (WIN_VER / 2-10);//random y-start-position
		ball->setPos(WIN_HOR/2, newy);
	}

	Draw();
}

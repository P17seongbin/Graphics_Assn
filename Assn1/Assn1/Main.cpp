#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "System.h"
#include "Player.h"
#include "Ball.h"

#define WIN_HOR 100
#define WIN_VER 100
using namespace std;
void ReShape(int w, int h);
//void keyPlayer1(unsigned char, int, int);
//void keyPlayer2(int, int, int);

KeyHandler keyhandler;
GameManager GM;

void StepCaller(int dt) { GM.Step(dt);	glutTimerFunc(TIMEPERFRAME, StepCaller, TIMEPERFRAME); }
void AsciiKeyPress(unsigned char key, int x, int y);
void AsciiKeyRelease(unsigned char key, int x, int y);
void SpecialKeyPress(int key, int x, int y);
void SpecialKeyRelease(int key, int x, int y);
void DrawCaller() { GM.Draw(); }

void InitScene(void) 
{
	//Create Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Example");
	glClearColor(0.6, 0.8, 1.0, 0);
	glShadeModel(GL_FLAT);

} 
void RegisterCallback()
{
	glutDisplayFunc(DrawCaller); 
	glutReshapeFunc(ReShape);
	glutTimerFunc(TIMEPERFRAME, StepCaller, TIMEPERFRAME);
	glutKeyboardFunc(AsciiKeyPress);
	glutSpecialFunc(SpecialKeyPress);
	glutKeyboardUpFunc(AsciiKeyRelease);
	glutSpecialUpFunc(SpecialKeyRelease);
}

int main(int argc, char **argv)
{
	Ball ball;
	Player player1(&keyhandler, true);
	Player player2(&keyhandler, false);
	Net net(49, 0, 25,2);
		
	player1.setPos(15, 0);
	player2.setPos(65.0, 0);
	GM.addObject("player2", &player2);
	GM.addObject("player1", &player1);
	GM.addObject("ball", &ball);//ball must be GM[2]!! -> Step func. 참고
	GM.addObject("net", &net);
	glutInit(&argc,argv);
	   
	InitScene();

	RegisterCallback();
	//기타등등 시작하기 전에 필요한 것들
	
	//앱 시작!R
	glutMainLoop();
}

void ReShape(int w, int h) 
{
	glLoadIdentity(); //Stack matrix = I
	glViewport(0, 0, w, h); 
	gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
}

void AsciiKeyPress(unsigned char key, int x, int y)
{
	printf("1");
	float _x = GM.getObjectList()[2].second->getPos().first;
	float _y = GM.getObjectList()[2].second->getPos().second;
	float size = 20;
	float new_x=_x-size;
	float new_y = _y - size;
	if (key == 'x')//카메라 스위치
	{
		glLoadIdentity();
		if (_x < size)
			new_x = 0;
		else if (_x > (float)WIN_HOR - size)
			new_x = (float)WIN_HOR -2.0*size;

		if (_y < size)
			new_y = 0;
		else if (_y > (float)WIN_VER - size)
			new_y = (float)WIN_VER - 2.0*size;

		gluOrtho2D(new_x,new_x+2*size,new_y,new_y+2*size);
	}
	
		keyhandler.AsciiKeyPress(key, x, y);
}
void AsciiKeyRelease(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		glLoadIdentity();
		gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
	}
	keyhandler.AsciiKeyRelease(key, x, y);
}
void SpecialKeyPress(int key, int x, int y)
{
	keyhandler.SpecialKeyPress(key, x, y);
}
void SpecialKeyRelease(int key, int x, int y)
{
	keyhandler.SpecialKeyRelease(key, x, y);
}


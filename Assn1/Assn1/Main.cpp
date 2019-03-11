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


void StepCaller(int dt)
{
	GM.Step(dt);
	glutTimerFunc(TIMEPERFRAME, StepCaller, TIMEPERFRAME);
}

void DrawCaller()
{
	GM.Draw();
}
void AsciiKeyPress(unsigned char key, int x, int y)
{
	keyhandler.AsciiKeyPress(key, x, y);
}
void AsciiKeyRelease(unsigned char key, int x, int y)
{
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

void InitScene(void) 
{
	//Create Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Example");
	glClearColor(0.0, 0.0, 0.0, 0.0);
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
	//our players
	Player player1(&keyhandler, true);
	Player player2(&keyhandler, false);
	ball.setRadius(10);
	GM.addObject("ball",&ball);
	player1.setPos(0, 0);
	player2.setPos(50.0, 0);
	GM.addObject("player2", &player2);
	GM.addObject("player1", &player1);
	
	glutInit(&argc,argv);
	   
	InitScene();

	RegisterCallback();
	//기타등등 시작하기 전에 필요한 것들
	//DoSomeThing();

	//앱 시작!
	glutMainLoop();
}

void ReShape(int w, int h) 
{
	glLoadIdentity(); //Stack matrix = I
	glViewport(0, 0, w, h); 
	gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
}


/*
void keyPlayer1(unsigned char key, int x, int y)
{
	if (key == 'z')
		player1.setSpeed(-1 * SPEED, 0);
	if (key == 'c')
		player1.setSpeed(SPEED, 0);
}
void keyPlayer2(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		player2.setSpeed(-1 * SPEED, 0);
	}
	if (key == GLUT_KEY_RIGHT) {
		player2.setSpeed(SPEED, 0);
	}
}*/
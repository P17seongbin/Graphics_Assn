#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "System.h"
#include "Player.h"
#include "Ball.h"

#define MAX(x,y) (x > y ? x : y)
#define MIN(x,y) (x > y ? y : x)
#define WIN_HOR 100
#define WIN_VER 100
#define CAM_SIZE 20
#define BALL_SIZE 20
using namespace std;
void ReShape(int w, int h);
//void keyPlayer1(unsigned char, int, int);
//void keyPlayer2(int, int, int);

KeyHandler keyhandler;
GameManager GM;

void setOrtho2D();
void StepCaller(int dt) { GM.Step(dt);	setOrtho2D(); glutTimerFunc(TIMEPERFRAME, StepCaller, TIMEPERFRAME); }
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
void setOrtho2D()
{
	glLoadIdentity();
	if (keyhandler.isAsciiKeyPressed('x'))
	{
		std::pair<float, float> pos = GM.findObjectwithTag("ball")->getPos();
		float size = CAM_SIZE;

		pos = make_pair(
			MAX(MIN(WIN_HOR - RADIUS, pos.first), RADIUS),
			MAX(MIN(WIN_VER - RADIUS, pos.second), RADIUS)
		);

		std::pair<float, float> cam_pos = pos;

		cam_pos = make_pair(
			MAX(MIN(WIN_HOR - size, pos.first), size),
			MAX(MIN(WIN_VER - size, pos.second), size)
		);		
		gluOrtho2D(cam_pos.first - size, cam_pos.first + size, cam_pos.second - size, cam_pos.second + size);
	}
	else
		gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
}
void RegisterObject()
{
	Ball* ball = new Ball();
	Player* player1 = new Player(&keyhandler, true);
	Player* player2 = new Player(&keyhandler, false);
	Net* net = new Net(49, 0, 25, 2);

	player1->setPos(15, 0);
	player2->setPos(65.0, 0);
	GM.addObject("player2", player2);
	GM.addObject("player1", player1);
	GM.addObject("ball", ball);//ball must be GM[2]!! -> Step func. 참고
	GM.addObject("net", net);
}
int main(int argc, char **argv)
{
	RegisterObject();
	glutInit(&argc, argv);
	InitScene();
	RegisterCallback();
	//기타등등 시작하기 전에 필요한 것들
	//앱 시작!
	glutMainLoop();
}

void ReShape(int w, int h)
{
	glLoadIdentity(); //Stack matrix = I
	gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
	glViewport(0, 0, w, h);
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


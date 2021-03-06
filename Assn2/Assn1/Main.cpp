#include "Assn2.h"
#include <cstdlib>
#include <ctime>
KeyHandler keyhandler;
GameManager GM;

void AsciiKeyPress(unsigned char key, int x, int y) { keyhandler.AsciiKeyPress(key, x, y); }
void AsciiKeyRelease(unsigned char key, int x, int y) { keyhandler.AsciiKeyRelease(key, x, y); }
void SpecialKeyPress(int key, int x, int y) { keyhandler.SpecialKeyPress(key, x, y); }
void SpecialKeyRelease(int key, int x, int y) { keyhandler.SpecialKeyRelease(key, x, y); }

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));

	RegisterObject(&GM,&keyhandler);
	glutInit(&argc, argv);
	InitScene();
	RegisterCallback();
	//앱 시작!
	glutMainLoop();
}

void InitScene(void)
{
	//Create Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Example");
	glClearColor(0.6, 0.8, 1.0, 0);
	glShadeModel(GL_FLAT);
	PrintHelpText();
}

void Control2P()
{
	//Reset 2P Control info
	keyhandler.SpecialKeyRelease(GLUT_KEY_LEFT, 0, 0);//go left
	keyhandler.SpecialKeyRelease(GLUT_KEY_RIGHT, 0, 0);//go right

	//공 위치를 따라간다.
	float ballx = GM.findObjectwithTag("ball")->getPos().first;
	float pos = GM.findObjectwithTag("player2")->getPos().first;
	if (pos - ballx > P2_TOLERANCE)//허용치가 매 프레임마다 바뀌므로, 간헐적으로 반응 속도가 느려지는 현상(실수)를 재현.
	{
		keyhandler.SpecialKeyPress(GLUT_KEY_LEFT, 0,0);//go left
	}
	else if (ballx - pos > P2_TOLERANCE)
	{
		keyhandler.SpecialKeyPress(GLUT_KEY_RIGHT, 0, 0);//go right
	}
}

void DrawCaller() { if (keyhandler.isAsciiKeyPressed(' ')) GM.Draw(); }

void StepCaller(int dt) {
	if ((keyhandler.isAsciiKeyPressed('R') || keyhandler.isAsciiKeyPressed('r')) )
		GM.Restart();
	if (keyhandler.isAsciiKeyPressed(' '))
	{
		GM.Step(dt);
		setOrtho2D(&GM, &keyhandler);
		Control2P();
	}
	else
	{
		PrintHelpText();
	}
	glutTimerFunc(TIMEPERFRAME, StepCaller, TIMEPERFRAME);
}


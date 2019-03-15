#include "Assn1.h"

KeyHandler keyhandler;
GameManager GM;

int main(int argc, char **argv)
{
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

void DrawCaller() { GM.Draw(); }

void StepCaller(int dt) { GM.Step(dt);	setOrtho2D(&GM, &keyhandler); glutTimerFunc(TIMEPERFRAME, StepCaller, TIMEPERFRAME); }

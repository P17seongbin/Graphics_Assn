#include "Assn1.h"

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

void RegisterObject(GameManager* GM,KeyHandler* keyhandler)
{
	Ball* ball = new Ball();
	Player* player1 = new Player(keyhandler, true);
	Player* player2 = new Player(keyhandler, false);
	Net* net = new Net(49, 0, 25, 2);
	player1->setPos(15, 0);
	player2->setPos(65.0, 0);
	GM->addObject("player1", player1);
	GM->addObject("player2", player2);
	GM->addObject("ball", ball);
	GM->addObject("net", net);
}

void PrintHelpText()
{
	int size = 30;
	int ver_size = 5;
	std::pair<int, int> pos = make_pair((WIN_HOR - size) / 2, (WIN_VER + size) / 2);
	vector<string> how2play = { "Press z and c to control player","get 15 points first to win."," Press Space to start!" };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.5, 0.2);
	glBegin(GL_POLYGON);//draw 'window'
	glVertex2f(WIN_HOR / 2 - size, WIN_VER / 2 - size);
	glVertex2f(WIN_HOR / 2 - size, WIN_VER / 2 + size);
	glVertex2f(WIN_HOR / 2 + size, WIN_VER / 2 + size);
	glVertex2f(WIN_HOR / 2 + size, WIN_VER / 2 - size);
	glEnd();

	glColor3f(0, 0, 0);//print message
	for (int i = 0; i<how2play.size(); i++)
	{
		glRasterPos2f(pos.first, pos.second);
		for (int j = 0; j < how2play[i].length(); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, how2play[i][j]);
		}
		pos = make_pair(pos.first , pos.second - ver_size);
	}
	//glutPostRedisplay();
	glutSwapBuffers();
}

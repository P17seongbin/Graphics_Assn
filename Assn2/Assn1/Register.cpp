#include "Assn2.h"

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
	ball->setColor(1, 0, 0);

	Player* player1 = new Player(keyhandler, true);
	player1->setColor(1, 1, 0.2);
	std::pair<float,float> size = player1->getSize();
	float head_rad = 0.4 * size.first / 2;
	UnitCircle* h = new UnitCircle(size.second / 2, size.first + head_rad, head_rad, player1);
	h->setColor(1, 1, 0.2);
	player1->addChild(h);
	GM->addObject("h1", h);

	UnitTri* t_branch = new UnitTri(0,0, player1);
	t_branch->setColor(0.2, 0.2, 1);
	player1->addChild(t_branch);
	UnitTri* t_leaf = new UnitTri(-3, 5, t_branch);
	t_leaf->setColor(1, 0.4, 0.6);
	t_branch->addChild(t_leaf);

	//don't need to add to game manager....do we?


	Player* player2 = new Player(keyhandler, false);
	player2->setColor(1, 1, 0.2);
	size = player2->getSize();
	head_rad = 0.4*size.first / 2;
	h = new UnitCircle(size.second / 2, size.first + head_rad, head_rad, player2);
	h->setColor(1, 1, 0.2);
	player2->addChild(h);
	GM->addObject("h2", h);

	UnitRect* net = new UnitRect(49, 0, 25, 2);
	net->setColor(1, 0, 1);

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

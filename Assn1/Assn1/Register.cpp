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


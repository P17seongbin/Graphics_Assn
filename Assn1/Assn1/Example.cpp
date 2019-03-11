#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "System.h"

#define WIN_HOR 100
#define WIN_VER 100
using namespace std;
void myReshape(int w, int h);
void keyPlayer1(unsigned char, int, int);
void keyPlayer2(int, int, int);

GameManager GM;

class ExampleObject : public Object
{
public:
	ExampleObject()
	{
		tag = "Example";
	}
	void Step(int dt) override//매 Step마다 이동과 움직임을 구현
	{
		//Bad Code!
		if (pos.first < 0 || pos.first > 100) speed = make_pair(speed.first * -1,speed.second);
		if (pos.second < 0 || pos.second > 100)  speed = make_pair(speed.first,speed.second * -1);
		addPos(speed.first * dt, speed.second * dt);
	}
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override//지금은 충돌 안함
	{

	}
	void Draw() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(pos.first, pos.second);
		glVertex2f(pos.first, pos.second + size.first);
		glVertex2f(pos.first + size.second, pos.second + size.first);
		glVertex2f(pos.first + size.second, pos.second);
		glEnd();
	}
	void setSize(float x, float y) {
		size = make_pair(x, y);
	}
private:
	std::pair<float, float> size;//width,height
};

//our players
Player player1;
Player player2;

void StepCaller(int dt)
{
	GM.Step(dt);
	glutTimerFunc(16, StepCaller, 16);
	glutPostRedisplay();
}
void DrawCaller()
{
	GM.Draw();
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
	glutReshapeFunc(myReshape);
	glutTimerFunc(16, StepCaller, 16);
	glutKeyboardFunc(keyPlayer1);
	glutSpecialFunc(keyPlayer2);
}

int main(int argc, char **argv)
{
	Ball ball;
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

void myReshape(int w, int h) 
{
	glLoadIdentity(); //Stack matrix = I
	glViewport(0, 0, w, h); 
	gluOrtho2D(0.0, WIN_HOR, 0.0, WIN_VER);
}

void keyPlayer1(unsigned char key, int x, int y)
{
	float speed = player1.getSpeed().first;
	if(key=='z')
		player1.addPos(-speed, 0);
	if(key=='c')
		player1.addPos(speed, 0);
	
	if (player1.getPos().first > WIN_HOR/2-player1.getSize().second)
	{
		player1.addPos(-speed, 0);
	}
	else if (player1.getPos().first <0)
		player1.addPos(speed, 0);
	glutPostRedisplay();
}
void keyPlayer2(int key, int x, int y)
{
	float speed = player2.getSpeed().first;

	if (key == GLUT_KEY_LEFT) {
		player2.addPos(-speed, 0);
	}
	if(key== GLUT_KEY_RIGHT){
		player2.addPos(speed, 0);
	}
	if (player2.getPos().first > WIN_HOR - player2.getSize().second)
	{
		player2.addPos(-speed, 0);
	}
	else if (player2.getPos().first < WIN_HOR/2)
		player2.addPos(speed, 0);
	glutPostRedisplay();
}